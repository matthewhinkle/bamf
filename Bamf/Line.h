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
		T * xMin = const_cast<T *>(&this->xMin);
		T * yMin = const_cast<T *>(&this->yMin);
		T * xMax = const_cast<T *>(&this->xMax);
		T * yMax = const_cast<T *>(&this->yMax);
	
		*xMin = line.xMin;
		*yMin = line.yMin;
		*xMax = line.xMax;
		*yMax = line.yMax;
		
		return *this;
	}
	
	inline bool intersects(const Aabb<T> & aabb) const {
		const bool x1Min = this->x1 < this->x2;
		T xMin = x1Min ? this->x1 : this->x2;
		T xMax = x1Min ? this->x2 : this->x1;
		
		const bool y1Min = this->y1 < this->y2;
		T yMin = y1Min ? this->y1 : this->y2;
		T yMax = y1Min ? this->y2 : this->y1;
	
		if(xMin > aabb.xMax || xMax < aabb.xMin || yMin > aabb.yMax || yMax < aabb.yMin) {
			std::cout << "badd" << std::endl;
			return false;
		} else {
			std::cout << "finally" << std::endl;
		}
	
		const R m = static_cast<R>((this->y2 - this->y1)) / static_cast<R>((this->x2 - this->x1));
		const R b = -(this->x1 * m) + this->y1;
		
		const T x0 = aabb.xMin;
		const R y0 = (m * x0) + b;
		if(y0 <= aabb.yMax && y0 >= aabb.yMin) {
			//assert(0);
			return true;
		}
		
		const T x1 = aabb.xMax;
		const R y1 = (m * x1) + b;
		if(y1 <= aabb.yMax && y1 >= aabb.yMin) {
			//assert(0);
			return true;
		}
		
		return false;
	}
	
	const T x1;
	const T x2;
	const T y1;
	const T y2;

};

}

#endif
