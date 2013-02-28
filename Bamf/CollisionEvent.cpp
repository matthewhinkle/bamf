//
//  CollisionEvent.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/20/13.
//
//

#include "CollisionEvent.h"


namespace bamf{
    
    CollisionEvent::CollisionEvent(CollisionShape * s1, CollisionShape * s2){
        shape1 = s1;
        shape2 = s2;
    }
    CollisionEvent::~CollisionEvent() {
        
    }
    CollisionShape * CollisionEvent::getShapeOne() {
        return shape1;
    }
    CollisionShape * CollisionEvent::getShapeTwo() {
        return shape2;
    }
    
    
}