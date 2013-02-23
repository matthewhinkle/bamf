//
//  CoreModule.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#include "CoreModule.h"

namespace bamf {

CoreModule::CoreModule()
	:
	graphicsModule(),
	sceneManager()
{ }

CoreModule::~CoreModule() { }

void CoreModule::init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	
	SDL_Init(SDL_INIT_VIDEO);
	
	this->graphicsModule.init();
}

void CoreModule::update(unsigned dt)
{
	this->sceneManager.update(dt);
}

void CoreModule::prepareGraphicsModule(unsigned dt)
{
	this->graphicsModule.update(dt);
}

void CoreModule::draw(unsigned dt)
{
	this->sceneManager.draw(this->graphicsModule.getSpriteStream(), dt);
}

}