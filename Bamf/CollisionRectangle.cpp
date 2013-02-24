//
//  CollisionRectangle.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionRectangle.h"
#include "CollisionCircle.h"

namespace bamf {
    CollisionRectangle::CollisionRectangle(glm::vec2 minimum, glm::vec2 maximum){
        min = minimum;
        max = maximum;
    }
    CollisionRectangle::~CollisionRectangle() {
        
    }
    bool CollisionRectangle::checkCollision(CollisionCircle c) {
        
        if(c.getPosition().y <= max.y ){
            return true;
        }
        
        return false;
    }
    
   
}