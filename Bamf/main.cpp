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

class MoveCameraAction : public Action
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

class MoveCameraButtons : public IKeyMapping
{
protected:
    int _keyCode;
    float _movesX;
    float _movesY;
    bamf::Camera * _cam;
public:
    MoveCameraButtons(int keyCode, float movesX, float movesY,  bamf::Camera * cam);
    bool appliesForInput(KeyPressType type, int keyCode, ...);
    Action * actionForInput();
};

MoveCameraButtons::MoveCameraButtons(int keyCode, float movesX, float movesY, bamf::Camera * cam)
{
    _keyCode = keyCode;
    _movesX = movesX;
    _movesY = movesY;
    _cam = cam;
}

bool MoveCameraButtons::appliesForInput(KeyPressType type, int keyCode, ...)
{
    if(keyCode == _keyCode && type == KEY_DOWN) {
        return true;
    }
    else {
        return false;
    }
}

Action * MoveCameraButtons::actionForInput()
{
    return new MoveCameraAction(_movesX, _movesY, _cam);
}

int main(int argc, char *argv[])
{
	bamf::ResourceManager man;
	
	bamf::Sprite sprite("/bamf/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getTexture()->getBounds().getCenter());
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window * window = SDL_CreateWindow("bamf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	
	glClearColor(0, 0, 0, 1);
	
	sprite.getTexture()->bind();
	
	bamf::Camera cam;
	const bamf::Rectangle & bounds = cam.getViewArea();
	float aspectRatio = static_cast<float>(bounds.width) / static_cast<float>(bounds.height);
	
	glm::mat4 proj = glm::perspective(90.0f, aspectRatio, 0.01f, 100.0f);
	
	bamf::MatrixStack ms;
	bamf::SpriteStream spriteStream(&cam);
	
    InputManager inputManager;
    
    InputMapping inputMapping;
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_RIGHT, .1, 0, &cam));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_LEFT, -.2, 0, &cam));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_UP, 0, .1, &cam));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_DOWN, 0, -.1, &cam));
    
    inputManager.setInputMapping(&inputMapping);
    
	while(true) {
		
		inputManager.processInput();
        
		glm::mat4 view = cam.computeTransform();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bamf::MatrixStack::setMatrixMode(bamf::kMatrixModeProjection);
		bamf::MatrixStack::loadMatrix(proj);
		bamf::MatrixStack::setMatrixMode(bamf::kMatrixModeModel);
		ms.push();
		ms.mult(view);
		
		spriteStream.begin(ms.top(), bamf::kSpriteStreamClipEdges);
		
		/*
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				glm::vec2 pos(i * 210, j * 300);
				spriteStream.draw(&sprite, pos);
			}
		}
		*/
		
		spriteStream.draw(&sprite, glm::vec2(0, 0));
		
		spriteStream.end();
		
		ms.pop();
		
		SDL_GL_SwapWindow(window);
	}
	
	man.unloadAllResources();
	
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
