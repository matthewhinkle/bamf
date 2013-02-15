//
//  SynchronousGameLoop.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__SynchronousGameLoop__
#define __Bamf__SynchronousGameLoop__

#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "GameLoop.h"
#include "Module.h"

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
	SynchronousGameLoop();
	virtual ~SynchronousGameLoop();
	
	inline void addModule(Module * module) { this->modules.push_back(module); }
	inline void removeModule(Module * module);
	
	inline bool isSuspended() const { return this->suspended; }
	
	/* GameLoop interface */
	virtual void restart();
	virtual void start();
	virtual void stop();
	virtual void suspend();
	
	int run();
	
private:
	static int run(void * loop);
	
	std::vector<Module *> modules;
		
	bool running;
	bool suspended;
	
	/* these objects are for implementing suspend, not for syncrhonization */
	SDL_mutex * suspendMutex;
	SDL_cond * suspendCond;
	
	SynchronousGameLoop(const SynchronousGameLoop &);
	SynchronousGameLoop & operator=(const SynchronousGameLoop &);
};

}

#endif /* defined(__Bamf__SynchronousGameLoop__) */
