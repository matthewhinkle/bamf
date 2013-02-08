//
//  SynchronousGameLoop.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

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
	this->stop();
	this->thread = NULL;
	
	SDL_DestroyCond(this->suspendCond);
	SDL_DestroyMutex(this->suspendMutex);
	this->suspendMutex = NULL;
}

void SynchronousGameLoop::restart()
{
	this->stop();
	this->start();
}

void SynchronousGameLoop::start()
{
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
	Uint32 timeLastTicked = SDL_GetTicks();
	
	while(this->running) {
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
		
		/* update(delta) . . . */
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