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
#include "MatrixStack.h"
#include "Module.h"
#include "Rectangle.h"
#include "SpriteStream.h"

namespace bamf {

class GraphicsModule : public Module {
public:

	GraphicsModule(int width = 1024, int height = 768, bool fullscreen = false);
	GraphicsModule(int x, int y, int width, int height, bool fullscreen = false);
	virtual ~GraphicsModule();
	
	inline Camera * getCamera() const { return this->camera; }
	inline SpriteStream * getSpriteStream() const { return this->spriteStream; }
	
	/* Module interface */
	void init();
	void update(unsigned delta);

private:
	Camera * camera;
	SpriteStream * spriteStream;
	bool inited;
	
	Rectangle windowBounds;
	bool fullscreen;
	
	SDL_GLContext glContext;
	SDL_Window * window;
		
	GraphicsModule(const GraphicsModule &);
	GraphicsModule & operator=(const GraphicsModule &);
};

}

#endif /* defined(__Bamf__GraphicsLoop__) */
