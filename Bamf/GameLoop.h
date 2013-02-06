//
//  GameLoop.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef Bamf_GameLoop_h
#define Bamf_GameLoop_h

namespace bamf {

/**
	Game loop interface
 */
class GameLoop {
public:

	explicit GameLoop() { }
	virtual ~GameLoop() { }

	/**
		@name	restart()
		@brief	restart the gameloop.  this method would typically
				be used to reset any temporary environment variables
				set in the game loop
	 */
	virtual void restart() = 0;

	/**
		@name	start()
		@brief	start the game loop if it is not currently running;
				otherwise, do nothing
	 */
	virtual void start() = 0;
	
	/**
		@name	stop()
		@brief	stop the game loop if it is currently running; otherwise,
				do nothing
	 */
	virtual void stop() = 0;
	
	/**
		@name	suspend()
		@brief	freeze the game loop in its current state.  to resume,
				call GameLoop::start()
	 */
	virtual void suspend() = 0;

private:
	GameLoop(const GameLoop &);
	GameLoop & operator=(const GameLoop &);
};

}

#endif
