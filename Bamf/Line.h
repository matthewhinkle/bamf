//
//  Line.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/11/13.
//
//

#ifndef Bamf_Line_h
#define Bamf_Line_h

#include "Aabb.h"

#include <iostream>

namespace bamf {

template<
	typename T = int,
	typename R = float
> class Line {
public:

	Line() { }

	Line(T x1, T y1, T x2, T y2)
		:
		x1(x1),
		y1(y1),
		x2(x2),
		y2(y2)
	{ }
	
	Line(const Line & line)
		:
		x1(line.x1),
		y1(line.y1),
		x2(line.x2),
		y2(line.y2)
	{ }
	
	virtual ~Line() { }
	
	Line & operator=(const Line & line) {
		this->x1 = line.x1;
		this->y1 = line.y1;
		this->x2 = line.x2;
		this->y2 = line.y2;
		
		return *this;
	}
	
	inline bool intersects(const Aabb<T> & aabb, bool verbose = true) const {	
		const bool x1Min = this->x1 <= this->x2;
		T xMin = x1Min ? this->x1 : this->x2;
		T xMax = x1Min ? this->x2 : this->x1;
		
		const bool y1Min = this->y1 <= this->y2;
		T yMin = y1Min ? this->y1 : this->y2;
		T yMax = y1Min ? this->y2 : this->y1;
		
		if(xMin > aabb.xMax || xMax < aabb.xMin || yMin > aabb.yMax || yMax < aabb.yMin) {
			return false;
		}

		R dy = static_cast<R>(y2 - y1);
		R dx = static_cast<R>(x2 - x1);
		if(!(dy) || !(dx)) {
			return true;
		}
		
		/* y = ax + b */
		R a = dy / dx;
		R b = -(this->x1 * a) + this->y1;
		
		T x0 = aabb.xMin;
		R y0 = (a * x0) + b;
		if(y0 <= aabb.yMax && y0 >= aabb.yMin) {
			return true;
		}
		
		T x1 = aabb.xMax;
		R y1 = (a * x1) + b;
		if(y1 <= aabb.yMax && y1 >= aabb.yMin) {
			return true;
		}
		
		return false;
	}
	
	T x1;
	T x2;
	T y1;
	T y2;

};

}

#endif
