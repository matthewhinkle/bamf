//
//  BamfObject.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/14/13.
//
//

#include "BamfObject.h"

namespace bamf {
    
    uint64_t BamfObject::getObjectID() {
        return this->objectId;
    }
    
    void BamfObject::setObjectID(uint64_t objectID) {
        this->objectId = objectID;
    }
    
}