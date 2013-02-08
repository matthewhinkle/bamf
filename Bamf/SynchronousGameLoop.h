//
//  SynchronousGameLoop.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__SynchronousGameLoop__
#define __Bamf__SynchronousGameLoop__

#include "SDL2/SDL.h"

#include "GameLoop.h"

namespace bamf {

/**
	The instructions in a SynchronousGameLoop will execute
	each subsystem in order.  This does not guarentee that
	the current subsystem is the only running subsystem as
	previous subsystems may have spawned childen which are
	still running.
 */
class SynchronousGameLoop : public GameLoop {
public:

	/**
		Default Constructor
		
		@brief	create a new gameloop in a non-running state
	 */
	explicit SynchronousGameLoop();
	virtual ~SynchronousGameLoop();
	
	inline bool isSuspended() const { return this->suspended; }
	
	/* GameLoop interface */
	virtual void restart();
	virtual void start();
	virtual void stop();
	virtual void suspend();
	
private:
	static int run(void * loop);
	int run();
	
	bool running;
	bool suspended;
	
	SDL_Thread * thread;
	SDL_cond * suspendCond;
	SDL_mutex * suspendMutex;
};

}

#endif /* defined(__Bamf__SynchronousGameLoop__) */
