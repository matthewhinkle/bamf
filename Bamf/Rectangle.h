//
//  Rectangle.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef __Bamf__Rectangle__
#define __Bamf__Rectangle__

#include "glm/glm.hpp"

namespace bamf {

struct Rectangle {
public:

	explicit Rectangle(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f)
		:
		x(x),
		y(y),
		width(width),
		height(height)
	{ }
	
	Rectangle(const Rectangle & r)
		:
		x(r.x),
		y(r.y),
		width(r.width),
		height(r.height)
	{ }
	
	Rectangle & operator=(const Rectangle & r) {
		Rectangle clone(r);
		*this = clone;
		return *this;
	}
	
	virtual ~Rectangle() { }
	
	inline glm::vec2 getCenter() const { return glm::vec2(this->width >> 1, this->height >> 1); }

	inline int getBottom() const { return this->y + this->height; }
	inline int getLeft() const { return this->x; }
	inline int getRight() const { return this->x + this->width; }
	inline int getTop() const { return this->y; }

	const int x;
	const int y;
	const int width;
	const int height;
};

}

#endif /* defined(__Bamf__Rectangle__) */
