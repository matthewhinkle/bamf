//
//  MathCommons.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/7/13.
//
//

#ifndef Bamf_MathCommons_h
#define Bamf_MathCommons_h

#include "glm/glm.hpp"

namespace bamf {

class MathCommons {
public:

	static inline bool vectorsAreEqual(const glm::vec2 & v1, const glm::vec2 & v2, float epsilon = 0.1) {
		const glm::vec2 result = glm::abs(v2 - v1);
		
		return result.x < epsilon && result.y < epsilon;
	}

};

}

#endif
