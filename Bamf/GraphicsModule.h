//
//  GraphicsLoop.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/14/13.
//
//

#ifndef __Bamf__GraphicsLoop__
#define __Bamf__GraphicsLoop__

#include "Camera.h"
#include "Module.h"
#include "SpriteStream.h"

namespace bamf {

class GraphicsModule : public Module {
public:

	GraphicsModule(int width, int height);
	virtual ~GraphicsModule();
	
	inline Camera * getCamera() { return this->camera; }
	inline SpriteStream * getSpriteStream() { return this->spriteStream; }
	
	void init();
	void update(unsigned delta);

private:
	Camera * camera;
	SpriteStream * spriteStream;
	
	SDL_GLContext glContext;
	
	SDL_Window * window;
	
	ResourceManager man;
	
	GraphicsModule(const GraphicsModule &);
	GraphicsModule & operator=(const GraphicsModule &);
};

}

#endif /* defined(__Bamf__GraphicsLoop__) */
