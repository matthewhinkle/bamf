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

	Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
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
		this->x = r.x;
		this->y = r.y;
		this->width = r.width;
		this->height = r.height;
		
		return *this;
	}
	
	virtual ~Rectangle() { }
	
	inline glm::vec2 getCenter() const { return glm::vec2((this->x + this->width) >> 1, (this->y + this->height) >> 1); }

	inline int getBottom() const { return this->y; }
	inline int getLeft() const { return this->x; }
	inline int getRight() const { return this->x + this->width; }
	inline int getTop() const { return this->y + this->height; }
	
	inline bool isPointOutside(const glm::vec2 & v) const {	
		return v.x < this->x
		    || v.x > (this->x + this->width)
		    || v.y < this->y
			|| v.y > (this->y + this->height);
	}
	
	inline bool operator==(const Rectangle & r) {
		return this->x == r.x
		    && this->y == r.y
			&& this->width == r.width
			&& this->height == r.height;
	}

	int x;
	int y;
	int width;
	int height;
};

}

#endif /* defined(__Bamf__Rectangle__) */
