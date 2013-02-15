//
//  main.m
//  Bamf
//
//  Created by Matthew Hinkle on 1/31/13.
//
//

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include <iostream>

#include "Texture2D.h"
#include "Texture2DLoader.h"
#include "ResourceLoader.h"
#include "ResourceManager.h"
#include "SynchronousGameLoop.h"
#include "ImageResource.h"
#include "MatrixStack.h"

#include "Sprite.h"
#include "SpriteStream.h"
#include "Rectangle.h"

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
	
	SDL_Window * window = SDL_CreateWindow("bamf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	bamf::Camera cam;
	bamf::SpriteStream spriteStream(&cam);
	
	SDL_GL_SetSwapInterval(1);
	
	glClearColor(0, 0, 0, 1);
	
	bamf::MatrixStack ms;	
	bamf::InputManager inputManager;
	
	bamf::ResourceManager man;
	bamf::Sprite sprite("/bamf/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	
	bamf::Sprite hair("/bamf/crosshair.png");
	hair.load(man);
	hair.setHotspot(hair.getBounds().getCenter());
    
	glm::mat4 perspective = glm::perspective(90.0f, 1024.0f / 768.0f, -1.0f, 1.0f);
	
	
    bamf::InputMapping inputMapping;
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_RIGHT, 5, 0, &cam));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_LEFT, -5, 0, &cam));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_UP, 0, 5, &cam));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_DOWN, 0, -5, &cam));
    
    inputManager.setInputMapping(&inputMapping);

	std::vector<bamf::Module *> modules;
    modules.push_back(&inputManager);
	glm::vec2 pos;
    Uint32 timeLastTicked = SDL_GetTicks();
	while(true) {
        Uint32 time = SDL_GetTicks();
        Uint32 delta = time - timeLastTicked;
        timeLastTicked = time;
        
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		//inputManager.processInput();
		
        //will be in graphics module
		bamf::MatrixStack::setMatrixMode(bamf::kMatrixModeProjection);
		bamf::MatrixStack::loadMatrix(perspective);
		bamf::MatrixStack::setMatrixMode(bamf::kMatrixModeModel);
		ms.push();
		ms.mult(cam.computeTransform());
		
		spriteStream.begin(ms.top(), bamf::kSpriteStreamClipEdges);
		for(int i = 0; i < 1; i++) {
			for(int j = 0; j < 1; j++) {
				spriteStream.draw(&sprite, glm::vec2(i * 200, j * 300));
			}
		}
		spriteStream.end();
		
		spriteStream.begin(cam.computeTransform(), bamf::kSpriteStreamClipEdges);
		spriteStream.draw(&hair, cam.getPosition());
		spriteStream.end();
		
		bamf::MatrixStack::loadMatrix(glm::mat4());
		ms.pop();
		
		SDL_GL_SwapWindow(window);
        //end graphics stuff
		
        //calling modules
		std::vector<bamf::Module *>::iterator modIt;
		for (modIt = modules.begin(); modIt != modules.end(); modIt++) {
			(*modIt)->update(delta);
		}
        SDL_Delay(0);
	}
    
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
