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

#include "glm/glm.hpp"

namespace bamf {

template<typename T>
class Aabb {
public:

	Aabb() { }

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
		this->xMin = aabb.xMin;
		this->yMin = aabb.yMin;
		this->xMax = aabb.xMax;
		this->yMax = aabb.yMax;
		
		return *this;
	}
	
	template<typename R>
	friend bool operator==(const Aabb<R> & a, const Aabb<R> & b);

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
	
	inline glm::vec2 center() const {
		return glm::vec2(
			this->xMin + (this->getWidth() / 2),
			this->yMin + (this->getHeight() / 2));
	}
	
	inline float centerDistance(const Aabb & aabb) const { return glm::distance(this->center(), aabb.center()); }
	
	inline T getWidth() const { return this->xMax - this->xMin; }
	inline T getHeight() const { return this->yMax - this->yMin; }

	T xMin;
	T yMin;
	T xMax;
	T yMax;
};

template<typename R>
bool operator==(const Aabb<R> & a, const Aabb<R> & b)
{
	return a.xMin == b.xMin
		&& a.yMin == b.yMin
		&& a.xMax == b.xMax
		&& a.yMax == b.yMax;
}

}

#if 0
/*
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
*/
#endif

#endif
