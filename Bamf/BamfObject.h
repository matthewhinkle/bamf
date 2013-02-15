//
//  Bamf.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef Bamf_Bamf_h
#define Bamf_Bamf_h

#include <iostream>
#include "glm/glm.hpp"

namespace bamf {

/**
	First class game object interface
 */
class BamfObject {
private:
    uint64_t objectId;
public:

	explicit BamfObject();
	
	virtual glm::vec2 getPosition() const;
    
    uint64_t getObjectID();
    void setObjectID(uint64_t objectID);
	
private:
	BamfObject(const BamfObject &);
	BamfObject & operator=(const BamfObject &);
};

}

#endif
