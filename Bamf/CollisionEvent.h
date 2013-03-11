//
//  CollisionEvent.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/20/13.
//
//

#ifndef __Bamf__CollisionEvent__
#define __Bamf__CollisionEvent__

#include <iostream>
#include "CollisionShape.h"
#include "CollisionRectangle.h"

namespace bamf {
 
    class CollisionEvent {
    public:
        CollisionEvent(CollisionRectangle * s1, CollisionRectangle * s2, glm::vec2 v);
        ~CollisionEvent();
        CollisionRectangle * getShapeOne();
        CollisionRectangle* getShapeTwo();
        glm::vec2 getMtv();
    protected:
        
    private:
        CollisionRectangle * shape1;
        CollisionRectangle * shape2;
        glm::vec2 mtv;

    };
}
#endif /* defined(__Bamf__CollisionEvent__) */
