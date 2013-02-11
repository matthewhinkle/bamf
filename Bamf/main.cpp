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

int main(int argc, char *argv[])
{
	bamf::Camera cam;
	
	bamf::ResourceManager man;
	
	bamf::Sprite sprite("/Users/mike/Desktop/mage.png");
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
	
	const bamf::Rectangle & bounds = cam.getViewArea();
	float aspectRatio = static_cast<float>(bounds.width) / static_cast<float>(bounds.height);
	
	glm::mat4 proj = glm::perspective(90.0f, aspectRatio, 0.01f, 100.0f);
	
	bamf::MatrixStack ms;
	bamf::SpriteStream spriteStream;
	
	while(true) {
		SDL_Event e;
		if(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				break;
			}

			glm::vec2 position(cam.getPosition());
			switch(e.type) {
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
					case SDLK_RIGHT:
						position[0] += 0.1;
						break;
					case SDLK_LEFT:
						position[0] -= 0.1;
						break;
					case SDLK_DOWN:
						position[1] -= 0.1;
						break;
					case SDLK_UP:
						position[1] += 0.1;
						break;
					}
					break;
			}
			
			cam.setPosition(position);
		}
		
		glm::mat4 view = cam.computeTransform();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bamf::MatrixStack::setMatrixMode(bamf::kMatrixModeProjection);
		bamf::MatrixStack::loadMatrix(proj);
		bamf::MatrixStack::setMatrixMode(bamf::kMatrixModeModel);
		ms.push();
		ms.mult(view);
		
		spriteStream.begin(ms.top());
		
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				glm::vec2 pos(i * 210, j * 300);
				spriteStream.draw(&sprite, pos);
			}
		}
		
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
