//
//  Hashes.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/11/13.
//
//

#ifndef Bamf_Hashes_h
#define Bamf_Hashes_h

#include <unordered_map>

#include "glm/glm.hpp"

#include "Aabb.h"

namespace std {

template<> struct hash<glm::vec2> {
	size_t operator()(const glm::vec2 & v) const {
		return hash<float>()(v.x) ^ hash<float>()(v.y);
	}
};

template<> struct hash<bamf::Aabb<int>> {
	size_t operator()(const bamf::Aabb<int> & aabb) const {
		hash<int> hash;
		
		return hash(aabb.xMin)
		     ^ hash(aabb.yMin)
			 ^ hash(aabb.xMax)
			 ^ hash(aabb.yMax);
	}
};

}

#endif
