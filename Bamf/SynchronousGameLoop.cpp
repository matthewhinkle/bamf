//
//  SynchronousGameLoop.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#include "SynchronousGameLoop.h"

#include "Lerp.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "SpriteStream.h"
#include "GraphicsModule.h"

bamf::Sprite sprite("/bamf/mage.png");
bamf::Sprite crosshair("/bamf/crosshair.png");

extern bamf::GraphicsModule * graphicsModule;

namespace bamf {

SynchronousGameLoop::SynchronousGameLoop()
	:
	running(false),
	suspended(false),
	suspendMutex(SDL_CreateMutex()),
	suspendCond(SDL_CreateCond()),
	dt(0.016),
	maxDtFrame(60)
{ }

SynchronousGameLoop::~SynchronousGameLoop()
{
	if(this->suspendMutex) {
		SDL_DestroyMutex(this->suspendMutex);
		this->suspendMutex = NULL;
	}
	
	if(this->suspendCond) {
		SDL_DestroyCond(this->suspendCond);
		this->suspendCond = NULL;
	}
}

void SynchronousGameLoop::removeModule(Module * module)
{
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		if(*modIt == module) {
			this->modules.erase(modIt);
			
			return;
		}
	}
}

void SynchronousGameLoop::restart()
{
	this->stop();
	this->start();
}

void SynchronousGameLoop::start()
{
	if(__sync_bool_compare_and_swap(&this->running, false, true)) {
		this->run();
	} else if(this->suspended) {
		this->suspended = false;
		SDL_CondSignal(this->suspendCond);
	}
}

void SynchronousGameLoop::stop()
{
	if(!(__sync_bool_compare_and_swap(&this->running, true, false))) {
		/* game loop is not currently running */
		return;
	}
}

void SynchronousGameLoop::suspend()
{
	this->suspended = true;
}
	
float SynchronousGameLoop::update(float epoch)
{
	for(; epoch >= this->dt; epoch -= this->dt) {
	
	}
	
	return epoch > 0.0f ? epoch : 0.0f;
}

void SynchronousGameLoop::draw(unsigned delta) {
	/* temp draw code */
	SpriteStream * ss = graphicsModule->getSpriteStream();
	
	ss->begin(graphicsModule->getCamera()->computeTransform(), bamf::kSpriteStreamClipEdges | bamf::kSpriteStreamEnforceDrawOrder);
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 2; j++) {
			ss->draw(&sprite, glm::vec2(i * 200, j * 300));
		}
	}
	ss->draw(&crosshair, graphicsModule->getCamera()->getPosition());
	ss->end();
	
	/* actual code */
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		(*modIt)->update(delta);
	}
}

int SynchronousGameLoop::run()
{
	/* temp development code */
	ResourceManager man;
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	
	crosshair.load(man);
	crosshair.setHotspot(crosshair.getBounds().getCenter());
	
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		(*modIt)->init();
	}
	
	unsigned timeLastTicked = SDL_GetTicks();
	float epoch = 0;
	while(this->running) {
		while(this->running && this->suspended) {
			SDL_CondWait(this->suspendCond, this->suspendMutex);
		}
			
		if(!(this->running)) {
			/* do not execute another iteration if we stopped while suspended */
			continue;
		}
		
		unsigned time = SDL_GetTicks();
		unsigned dtFrame = glm::min(time - timeLastTicked, maxDtFrame);
		timeLastTicked = time;
		epoch += dtFrame / 1000.0f;
		printf("dtFrame = %u\n", dtFrame);
		
		/* interpolate */
		//Lerp::frameRate()
		
		epoch = this->update(epoch);
		
		this->draw(this->dt);
	}
		return 0;
}

}