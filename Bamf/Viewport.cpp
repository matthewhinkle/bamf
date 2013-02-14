//
//  Viewport.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/11/13.
//
//

#include "Viewport.h"

static inline bamf::Rectangle getViewport();

namespace bamf {

Viewport::Viewport(float angle, float zNear, float zFar)
	:
	Viewport(getViewport(), angle, zNear, zFar)
{ }

Viewport::Viewport(const Rectangle & bounds, float angle, float zNear, float zFar)
	:
	bounds(bounds)
{
	this->setPerspective(bounds, angle, zNear, zFar);
}

Viewport::~Viewport() { }

const glm::mat4 & Viewport::setPerspective(float angle, float zNear, float zFar)
{
	return this->setPerspective(getViewport(), angle, zNear, zFar);
}

const glm::mat4 & Viewport::setPerspective(const Rectangle & bounds, float angle, float zNear, float zFar)
{
	SDL_assert(bounds.width != 0);
	float aspectRatio = static_cast<float>(bounds.width / bounds.height);
	return this->perspective = glm::perspective(angle, aspectRatio, zNear, zFar);
}

void Viewport::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}

static inline bamf::Rectangle getViewport()
{
	GLint v[4];
	glGetIntegerv(GL_VIEWPORT, v);
	
	return bamf::Rectangle(v[0], v[1], v[2], v[3]);
}