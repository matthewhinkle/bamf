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
		std::cout << c.getPosition().y << std::endl;
        if(c.getPosition().y <= -200){
            return true;
        }
        
        return false;
    }
    
   
}