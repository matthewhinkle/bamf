//
//  CoreModule.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#ifndef __Bamf__CoreModule__
#define __Bamf__CoreModule__

#include "SDL2/SDL.h"

#include "Module.h"
#include "GraphicsModule.h"
#include "SceneManager.h"

namespace bamf {

class CoreModule : public Module {
public:

	CoreModule();
	virtual ~CoreModule();
	
	inline GraphicsModule * getGraphicsModule() { return &this->graphicsModule; }
	
	inline SceneManager * getSceneManager() { return &this->sceneManager; }
	
	/* Module interface */
	void init();
	void update(Scene * scene, unsigned dt);
	
	void prepareGraphicsModule(unsigned dt);
	
	void draw(unsigned dt);

private:
	GraphicsModule graphicsModule;
	
	SceneManager sceneManager;

	CoreModule(const CoreModule &);
	CoreModule & operator=(const CoreModule &);
};

}

#endif /* defined(__Bamf__CoreModule__) */
