//
//  main.m
//  Bamf
//
//  Created by Matthew Hinkle on 1/31/13.
//
//

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "ResourceManager.h"
#include "SynchronousGameLoop.h"

#include "Camera.h"

#include "InputManager.h"
#include "InputMapping.h"
#include "Action.h"

#include "Module.h"
#include "GraphicsModule.h"

class MoveCameraAction : public bamf::Action
{
protected:
    float _x;
    float _y;
    bamf::Camera * _camera;
public:
    MoveCameraAction(float x, float y, bamf::Camera * camera);
    void executeAction();
};

MoveCameraAction::MoveCameraAction(float x, float y, bamf::Camera * camera)
{
    _x = x;
    _y = y;
    _camera = camera;
}

void MoveCameraAction::executeAction()
{
    glm::vec2 position = _camera->getPosition();
    position.x += _x;
    position.y += _y;
    _camera->setPosition(position);
}

class MoveCameraButtons : public bamf::IKeyMapping
{
protected:
    int _keyCode;
    float _movesX;
    float _movesY;
    bamf::Camera * _cam;
public:
    MoveCameraButtons(int keyCode, float movesX, float movesY,  bamf::Camera * cam);
    bool appliesForInput(bamf::KeyPressType type, int keyCode, ...);
    bamf::Action * actionForInput();
};

MoveCameraButtons::MoveCameraButtons(int keyCode, float movesX, float movesY, bamf::Camera * cam)
{
    _keyCode = keyCode;
    _movesX = movesX;
    _movesY = movesY;
    _cam = cam;
}

bool MoveCameraButtons::appliesForInput(bamf::KeyPressType type, int keyCode, ...)
{
    if(keyCode == _keyCode && type == bamf::KEY_DOWN) {
        return true;
    }
    else {
        return false;
    }
}

bamf::Action * MoveCameraButtons::actionForInput()
{
    return new MoveCameraAction(_movesX, _movesY, _cam);
}

int main(int argc, char *argv[])
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	
	SDL_Init(SDL_INIT_VIDEO);
	
	bamf::GraphicsModule graphicsModule;
	graphicsModule.init();
	
	bamf::GameLoop * gameLoop = new bamf::SynchronousGameLoop(&graphicsModule);
		
	bamf::InputManager inputManager;
	bamf::InputMapping inputMapping;
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_RIGHT, 1000 * 0.016, 0, graphicsModule.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_LEFT, -1000 * 0.016, 0, graphicsModule.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_UP, 0, 1000 * 0.016, graphicsModule.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_DOWN, 0, -1000 * 0.016, graphicsModule.getCamera()));
    
    inputManager.setInputMapping(&inputMapping);
	gameLoop->addModule(&inputManager);
	
	gameLoop->start();
	
	return 0;
}
