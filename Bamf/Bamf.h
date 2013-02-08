//
//  Bamf.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef Bamf_Bamf_h
#define Bamf_Bamf_h

#include "glm/glm.h"

namespace bamf {

/**
	First class game object interface
 */
class Bamf {
public:

	explicit Bamf();
	virtual ~Bamf() { }
	
	virtual glm::vec2 getPosition() const;
	
private:
	Bamf(const Bamf &);
	Bamf & operator=(const Bamf &);
};

}

#endif
