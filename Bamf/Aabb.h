//
//  Aabb.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/9/13.
//
//

#ifndef Bamf_Aabb_h
#define Bamf_Aabb_h

#include <unordered_map>
#include <utility>

namespace bamf {

template<typename T>
class Aabb {
public:

	Aabb(T xMin, T yMin, T xMax, T yMax)
		:
		xMin(xMin),
		yMin(yMin),
		xMax(xMax),
		yMax(yMax)
	{ }
	
	Aabb(const std::pair<T, T> & min, const std::pair<T, T> & max)
		:
		xMin(min.first),
		yMin(min.second),
		xMax(max.first),
		yMax(max.second)
	{ }
	
	Aabb(const Aabb & aabb)
		:
		xMin(aabb.xMin),
		yMin(aabb.yMin),
		xMax(aabb.xMax),
		yMax(aabb.yMax)
	{ }
	
	virtual ~Aabb() { }
	
	Aabb & operator=(const Aabb & aabb) {
		T * xMin = const_cast<T *>(&this->xMin);
		T * yMin = const_cast<T *>(&this->yMin);
		T * xMax = const_cast<T *>(&this->xMax);
		T * yMax = const_cast<T *>(&this->yMax);
	
		*xMin = aabb.xMin;
		*yMin = aabb.yMin;
		*xMax = aabb.xMax;
		*yMax = aabb.yMax;
		
		return *this;
	}

	inline bool intersects(const Aabb & aabb) const {
		return !(this->xMax < aabb.xMin
			  || this->xMin > aabb.xMax
			  || this->yMax < aabb.yMin
			  || this->yMin > aabb.yMax);
	}
	
	inline std::pair<T, T> getCenter() const {
		return std::pair<T, T>(
			this->xMin + (this->getWidth() / 2),
			this->yMin + (this->getHeight() / 2));
	}
	
	inline T getWidth() const { return this->xMax - this->xMin; }
	inline T getHeight() const { return this->yMax - this->yMin; }

	const T xMin;
	const T yMin;
	const T xMax;
	const T yMax;
};

}

namespace std {

template<typename T> struct hash<bamf::Aabb<T>> {
	size_t operator()(const bamf::Aabb<T> & aabb) {
		hash<T> hash;
	
		return hash(aabb.xMin)
		     ^ hash(aabb.yMin)
			 ^ hash(aabb.xMax)
			 ^ hash(aabb.yMax);
	}
};

}

#endif
