//
//  main.m
//  Bamf
//
//  Created by Matthew Hinkle on 1/31/13.
//
//

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>

#include "Texture2D.h"
#include "ResourceLoader.h"
#include "ResourceManager.h"
#include "PngImageLoader.h"
#include "SynchronousGameLoop.h"
#include "ImageResource.h"

int main(int argc, char *argv[])
{
	bamf::PngImageLoader loader;
	bamf::ResourceManager man;
	
	uint64_t id = man.loadResource("mage.png", loader);
	bamf::Resource * res = man.getResourceById(id);
	SDL_assert(res);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	
	SDL_Window * window = SDL_CreateWindow("bamf", 0, 0, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	
	glClearColor(0, 0, 0, 0);
	
	bamf::Texture2D t(1, static_cast<bamf::ImageResource *>(res));
	t.bind();
	
	float w = t.getWidth();
	float h = t.getHeight();
	
	GLfloat vertices[] = {
		0.0f, 0.0f,
		w, 0.0f,
		w, h,
		0.0f, h
	};
	
	GLfloat texVerts[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};
	
	GLuint buf[2];
	glGenBuffers(2, buf);
	
	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texVerts), texVerts, GL_STATIC_DRAW);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	while(true) {
		SDL_Event e;
		if(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				break;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, 800, 0.0, 600, -1.0, 1.0);
		glTranslatef(0.0f, 0.0f, 0.0f);
		
		t.bind();
		
		glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);

#if 0
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
		glDrawArrays(GL_QUADS, 0, 8);
		
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
#endif
		
		SDL_GL_SwapWindow(window);
	}
	
	man.unloadAllResources();
	
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
