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

namespace std {

template<> struct hash<glm::vec2> {
	size_t operator()(const glm::vec2 & v) {
		return hash<float>()(v.x) ^ hash<float>()(v.y);
	}
};

}

#endif
