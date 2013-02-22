//
//  GraphicsLoop.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/14/13.
//
//

#include "GraphicsModule.h"

/* constants */
static glm::mat4 kIdentMatrix;
static const char kWindowTitle[] = "bamf engine";

enum {
	kVerticalSync = 1
};

/* internal prototypes */
static inline void setClearColor();

namespace bamf {

GraphicsModule::GraphicsModule(int width, int height, bool fullscreen)
	:
	GraphicsModule(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, fullscreen)
{ }

GraphicsModule::GraphicsModule(int x, int y, int width, int height, bool fullscreen)
	:
	camera(NULL),
	spriteStream(NULL),
	windowBounds(x, y, width, height),
	fullscreen(fullscreen),
	inited(false)
{ }

GraphicsModule::~GraphicsModule()
{
	SDL_GL_DeleteContext(this->glContext);
	
	SDL_DestroyWindow(this->window);
	this->window = NULL;
	
	delete this->spriteStream;
	this->spriteStream = NULL;
	
	delete this->camera;
	this->camera = NULL;
}

void GraphicsModule::init()
{
	if(__sync_bool_compare_and_swap(&this->inited, false, true)) {
		this->window = SDL_CreateWindow(
			kWindowTitle,
			this->windowBounds.x,
			this->windowBounds.y,
			this->windowBounds.width == 0 ? 1 : this->windowBounds.width,
			this->windowBounds.height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (this->fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
		
		this->glContext = SDL_GL_CreateContext(window);
		
		this->camera = new Camera();
		this->spriteStream = new SpriteStream(this->camera);
				
		glClearColor(0, 0, 0, 1);
	}
}

void GraphicsModule::update(unsigned delta)
{
	Viewport * viewport = this->camera->getViewport();
	viewport->clear();

	MatrixStack::setMatrixMode(bamf::kMatrixModeProjection);
	MatrixStack::loadMatrix(viewport->getPerspective());
	MatrixStack::setMatrixMode(bamf::kMatrixModeModel);
	
	this->spriteStream->flush();
	
	MatrixStack::loadMatrix();
	
	SDL_GL_SwapWindow(this->window);
}

}

static inline void setClearColor() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}