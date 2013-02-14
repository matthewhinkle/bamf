//
//  SynchronousGameLoop.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#include "SDL2/SDL_opengl.h"

#include "SynchronousGameLoop.h"

namespace bamf {

SynchronousGameLoop::SynchronousGameLoop()
	:
	running(false),
	suspended(false),
	thread(NULL),
	suspendCond(SDL_CreateCond()),
	suspendMutex(SDL_CreateMutex())
{ }

SynchronousGameLoop::~SynchronousGameLoop()
{
	if(this->thread) {
		this->stop();
		this->thread = NULL;
	}
	
	if(this->suspendCond) {
		SDL_DestroyCond(this->suspendCond);
		this->suspendCond = NULL;
	}
	
	if(this->suspendMutex) {
		SDL_DestroyMutex(this->suspendMutex);
		this->suspendMutex = NULL;
	}
}

void SynchronousGameLoop::removeModule(Module * module)
{
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		if(*modIt == module) {
			this->modules.erase(modIt);
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
	this->running = true;
	this->run();
	return;

	if(!(__sync_bool_compare_and_swap(&this->running, false, true))) {
		/* game loop is already running.  check if we are suspended */
		
		SDL_mutexP(this->suspendMutex);
		if(this->suspended) {
			/* we are suspended */
			this->suspended = false;
			SDL_CondSignal(this->suspendCond);
		}
		SDL_mutexV(this->suspendMutex);
		
		return;
	}
	
	this->thread = SDL_CreateThread(SynchronousGameLoop::run, "SyncLoop", this);
	SDL_assert(this->thread);
}

void SynchronousGameLoop::stop()
{
	if(!(__sync_bool_compare_and_swap(&this->running, true, false))) {
		/* game loop is not currently running */
		return;
	}
	
	SDL_assert(this->thread);
	SDL_WaitThread(this->thread, NULL);
	
	SDL_mutexP(this->suspendMutex);
	this->suspended = false;
	SDL_mutexV(this->suspendMutex);
}

void SynchronousGameLoop::suspend()
{
	SDL_mutexP(this->suspendMutex);
	this->suspended = true;
	SDL_mutexV(this->suspendMutex);
}

int SynchronousGameLoop::run()
{
	std::vector<Module *>::iterator modIt;
	for (modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		(*modIt)->init();
	}
	
	//Uint32 timeLastTicked = SDL_GetTicks();
	while(this->running) {
		for (modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
			(*modIt)->update(0);
		}
	#if 0
		SDL_mutexP(this->suspendMutex);
		while(this->running && this->suspended) {
			SDL_CondWait(this->suspendCond, this->suspendMutex);
		}
		SDL_mutexV(this->suspendMutex);
			
		if(!(this->running)) {
			/* do not execute another iteration if we stopped while suspended */
			continue;
		}
		
		Uint32 time = SDL_GetTicks();
		Uint32 delta = time - timeLastTicked;
		timeLastTicked = time;
		
	#endif
	}
	
	return 0;
}

int SynchronousGameLoop::run(void * loop)
{
	SynchronousGameLoop * sgl = static_cast<SynchronousGameLoop *>(loop);
	if(sgl) {
		return sgl->run();
	}
	
	return 1;
}

}