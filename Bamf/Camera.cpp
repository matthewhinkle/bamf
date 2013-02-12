//
//  Camera.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/6/13.
//
//

#include "Camera.h"

/* internal prototypes */
static inline bamf::Rectangle getViewport();

namespace bamf {

Camera::Camera()
{
	this->setPosition(glm::vec2(0.0f, 0.0f));
	this->setRotation(0.0f);
	this->setZoom(1.0f);
	this->updateViewPortBounds();
}

Camera::~Camera() { }

void Camera::updateViewPortBounds()
{
	this->viewport = getViewport();
}

Rectangle Camera::getViewArea() const
{
	glm::vec2 position = this->position - this->viewport.getCenter();
	
	return Rectangle(
		position.x,
		position.y,
		position.x + viewport.width,
		position.y + viewport.height
	);
}

const glm::mat4 & Camera::computeTransform()
{
	return this->transform = this->translate * this->scale * this->rotate;
}

}

static inline bamf::Rectangle getViewport()
{
	GLint v[4];
	glGetIntegerv(GL_VIEWPORT, v);
	
	return bamf::Rectangle(v[0], v[1], v[2], v[3]);
}