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
#include "CollisionCircle.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"

enum {
	kMinFrameRenderTicks = 16
};

static inline float dtFrameToEpoch(float dtFrame);

namespace bamf {

SynchronousGameLoop::SynchronousGameLoop(CoreModule * coreModule)
	:
	running(false),
	suspended(false),
	suspendMutex(SDL_CreateMutex()),
	suspendCond(SDL_CreateCond()),
	ownCore(!(coreModule)),
	coreModule(coreModule ? coreModule : new CoreModule()),
	dt(0.016),
	maxDtFrame(60),
	time(0)
{
	this->addModule(this->coreModule);
}

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
	
	if(this->ownCore && this->coreModule) {
		delete this->coreModule;
		this->coreModule = NULL;
	}
	
	this->modules.clear();
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
    /* Collision Circle Test */
    CollisionCircle c1(glm::vec2(0,2), 2);
    CollisionCircle c2(glm::vec2(0,5), 1);    
    c1.checkCollision(c2);
    c2.checkCollision(c1);
    RigidBody r;
    r.setForce(glm::vec2(0,1));
    c2.setRigidBody(r);
    PhysicsWorld pw(1);
    pw.addObject(c2);
    
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		(*modIt)->init();
	}
	
	unsigned timeLastTicked = SDL_GetTicks();
	unsigned timeLastDrawn = timeLastTicked;
	
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

		//pw.update();		
		epoch += dtFrameToEpoch(dtFrame);
		epoch = this->update(epoch);
		
		if((time - timeLastDrawn) >= kMinFrameRenderTicks) {
			timeLastDrawn = this->time;
			this->draw(this->dt);
		}
	}
	
	return 0;
}

float SynchronousGameLoop::update(float epoch)
{
	for(; epoch >= this->dt; epoch -= this->dt, this->time += this->dt) {
		std::vector<Module *>::iterator modIt;
		for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
			(*modIt)->update(this->dt);
		}
	}
		
	return epoch > 0.0f ? epoch : 0.0f;
}

void SynchronousGameLoop::draw(unsigned dt) {
	this->coreModule->draw(dt);
	this->coreModule->prepareGraphicsModule(dt);
}

}

static inline float dtFrameToEpoch(float dtFrame) {
	return dtFrame / 1000.0f;
}
