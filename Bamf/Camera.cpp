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
}

Camera::~Camera() { }

Rectangle Camera::getViewArea() const
{
	Rectangle viewport = getViewport();
	
	return Rectangle(
		this->position[0],
		this->position[1],
		viewport.width,
		viewport.height
	);
}

glm::vec2 Camera::getViewPositionCenter() const
{
	Rectangle viewport = getViewport();
	glm::vec2 center = viewport.getCenter();
	
	return this->position + center;
}

const glm::mat4 & Camera::computeTransform()
{	
	glm::vec2 center = this->getViewPositionCenter();
	Rectangle viewport = getViewport();
	
	glm::mat4 centeredTranslate = glm::translate(glm::mat4(), -glm::vec3(center[0] / viewport.width, center[1] / viewport.height, 0.0f));
	
	return this->transform = this->translate * centeredTranslate * this->scale * this->rotate;
}

}

static inline bamf::Rectangle getViewport()
{
	GLint v[4];
	glGetIntegerv(GL_VIEWPORT, v);
	
	return bamf::Rectangle(v[0], v[1], v[2], v[3]);
}