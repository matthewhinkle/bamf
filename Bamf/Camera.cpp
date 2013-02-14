//
//  Camera.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/6/13.
//
//

#include "Camera.h"

namespace bamf {

Camera::Camera(Viewport * viewport)
{
	if(!(viewport)) {
		this->viewport = new Viewport();
	}

	this->setPosition(glm::vec2(0.0f, 0.0f));
	this->setRotation(0.0f);
	this->setZoom(1.0f);
}

Camera::~Camera()
{
	if(this->viewport) {
		delete this->viewport;
		this->viewport = NULL;
	}
}

Rectangle Camera::getViewArea() const
{
	const Rectangle & bounds = this->viewport->getBounds();
	glm::vec2 position = this->position - bounds.getCenter();
	
	return Rectangle(
		position.x,
		position.y,
		bounds.width,
		bounds.height
	);
}

const glm::mat4 & Camera::computeTransform()
{
	return this->transform = this->translate * this->scale * this->rotate;
}

}