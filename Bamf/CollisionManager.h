//
//  CollisionManager.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#ifndef __Bamf__CollisionManager__
#define __Bamf__CollisionManager__

#include <iostream>
#include <vector>
#include "CollisionShape.h"
#include "CollisionEvent.h"

namespace bamf {

class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();
    std::vector<CollisionEvent> getCollisions();
protected:
    
private:
    std::vector<CollisionShape> objectList;
    
};
}

#endif /* defined(__Bamf__CollisionManager__) */
