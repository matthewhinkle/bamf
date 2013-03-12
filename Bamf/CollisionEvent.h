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
#include "CollisionObject.h"
#include "CollisionShape.h"
#include "CollisionRectangle.h"

namespace bamf {
 
    class CollisionEvent {
    public:
        CollisionEvent(CollisionObject * s1, CollisionObject * s2, glm::vec2 v);
        ~CollisionEvent();
        CollisionObject * getShapeOne();
        CollisionObject* getShapeTwo();
        glm::vec2 getMtv();
    protected:
        
    private:
        CollisionObject * shape1;
        CollisionObject * shape2;
        glm::vec2 mtv;

    };
}
#endif /* defined(__Bamf__CollisionEvent__) */
