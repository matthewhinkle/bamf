//
//  SynchronousGameLoop.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#include "SynchronousGameLoop.h"

#include "Sprite.h"
#include "ResourceManager.h"
#include "SpriteStream.h"
#include "GraphicsModule.h"

extern bamf::GraphicsModule * graphicsModule;

namespace bamf {

SynchronousGameLoop::SynchronousGameLoop()
	:
	running(false),
	suspended(false),
	suspendMutex(SDL_CreateMutex()),
	suspendCond(SDL_CreateCond())
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

int SynchronousGameLoop::run()
{
	/* temp development code */
	ResourceManager man;
	Sprite sprite("/bamf/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	
	Sprite crosshair("/bamf/crosshair.png");
	crosshair.load(man);
	crosshair.setHotspot(crosshair.getBounds().getCenter());
	
	/* actual code */
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		(*modIt)->init();
	}

	Uint32 timeLastTicked = SDL_GetTicks();
	while(this->running) {
		while(this->running && this->suspended) {
			SDL_CondWait(this->suspendCond, this->suspendMutex);
		}
			
		if(!(this->running)) {
			/* do not execute another iteration if we stopped while suspended */
			continue;
		}
		
		unsigned time = static_cast<unsigned>(SDL_GetTicks());
		unsigned delta = time - timeLastTicked;
		timeLastTicked = time;
		
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
		for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
			(*modIt)->update(delta);
		}
	}
	
	return 0;
}

}