//
//  Viewport.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/11/13.
//
//

#ifndef __Bamf__Viewport__
#define __Bamf__Viewport__

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Rectangle.h"

namespace bamf {

class Viewport {
public:

	explicit Viewport(float angle = 90.0f, float zNear = -1.0f, float zFar = 1.0f);
	Viewport(const Rectangle & rectangle, float angle = 90.0f, float zNear = -1.0f, float zFar = 1.0f);
	virtual ~Viewport();
	
	inline const Rectangle & getBounds() const { return this->bounds; }
	inline const glm::mat4 & getPerspective() const { return this->perspective; }
	
	const glm::mat4 & setPerspective(float angle, float zNear = -1.0f, float zFar = 1.0f);
	const glm::mat4 & setPerspective(const Rectangle & bounds, float angle, float zNear = -1.0f, float zFar = 1.0f);
	
	void clear();
	
private:
	Rectangle bounds;
	
	glm::mat4 perspective;

	Viewport(const Viewport &);
	Viewport & operator=(const Viewport &);
};

}

#endif /* defined(__Bamf__Viewport__) */
