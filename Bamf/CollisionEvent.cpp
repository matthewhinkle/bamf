//
//  CollisionEvent.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/20/13.
//
//

#include "CollisionEvent.h"


namespace bamf{
    
    CollisionEvent::CollisionEvent(CollisionRectangle * s1, CollisionRectangle * s2, glm::vec2 v){
        shape1 = s1;
        shape2 = s2;
        mtv = v;
    }
    CollisionEvent::~CollisionEvent() {
        
    }
    CollisionRectangle * CollisionEvent::getShapeOne() {
        return shape1;
    }
    CollisionRectangle * CollisionEvent::getShapeTwo() {
        return shape2;
    }
    glm::vec2 CollisionEvent::getMtv() {
        return mtv;
    }
    
    
}