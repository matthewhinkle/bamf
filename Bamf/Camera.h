//
//  Camera.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/6/13.
//
//

#ifndef __Bamf__Camera__
#define __Bamf__Camera__

#include <cmath>

#include "SDL2/SDL_opengl.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Rectangle.h"

namespace bamf {

class Camera {
public:
	explicit Camera();
	virtual ~Camera();
	
	inline glm::vec2 getPosition() const { return this->position; }
	inline const float getRotation() const { return this->angle; }
	inline const float getZoom() const { return this->zoom; }
	
	inline void setPosition(const glm::vec2 & position) {
		this->position = position;
		this->translate = glm::translate(glm::mat4(), -glm::vec3(position[0], position[1], 1.0f));
	}
	
	inline void setRotation(float angle) {
		this->angle = glm::min(kRotationMax, glm::max(0.0f, angle));
		this->rotate = glm::rotate(glm::mat4(), this->angle, kZAxis);
	}
	
	inline void setZoom(float zoom) {
		this->zoom = glm::min(kZoomMax, glm::max(kZoomMin, zoom));
		this->scale = glm::scale(glm::mat4(), glm::vec3(zoom * kScaleScale, zoom * kScaleScale, 1.0f));
	}
	
	Rectangle getViewArea() const;
	glm::vec2 getViewPositionCenter() const;
	
	const glm::mat4 & computeTransform();

private:
	glm::vec2 position;
	
	glm::mat4 translate;
	glm::mat4 scale;
	glm::mat4 rotate;
	
	float angle;
	float zoom;
	
	glm::mat4 transform;
	
	const float kZoomMin = 0.01f;
	const float kZoomMax = 10.0f;
	const float kRotationMax = 2.0f * M_PI;
	const float kScaleScale = 0.003f;
	const glm::vec3 kZAxis = glm::vec3(0.0f, 0.0f, 1.0f);
};

}

#endif /* defined(__Bamf__Camera__) */
