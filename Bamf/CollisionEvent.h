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

namespace bamf {
 
    class CollisionEvent {
    public:
        CollisionEvent(CollisionShape * s1, CollisionShape * s2);
        ~CollisionEvent();
        CollisionShape* getShapeOne();
        CollisionShape* getShapeTwo();
    protected:
        
    private:
        CollisionShape * shape1;
        CollisionShape * shape2;

    };
}
#endif /* defined(__Bamf__CollisionEvent__) */
