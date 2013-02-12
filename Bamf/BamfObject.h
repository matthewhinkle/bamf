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
class BamfObject {
public:

	explicit BamfObject();
	virtual BamfObject() { }
	
	virtual glm::vec2 getPosition() const;
	
private:
	BamfObject(const BamfObject &);
	BamfObject & operator=(const BamfObject &);
};

}

#endif
