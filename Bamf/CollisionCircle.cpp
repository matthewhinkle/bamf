//
//  CollisionCircle.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionCircle.h"

namespace bamf {
    
    CollisionCircle::CollisionCircle(glm::vec2 p, int r)
    {
        //position = p;
        radius = r;
    }
    CollisionCircle::~CollisionCircle(){
        
    }
    /*bool CollisionCircle::checkCollision(CollisionCircle & c){
        glm::vec2 s = this->position - c.position;
        float radius = ((this->radius)+(c.radius));
        float magnitudeSquared = ((s.x)*(s.x))+((s.y)*(s.y));
        if(magnitudeSquared <= (radius * radius))
        {
            std::cout << "True";
            return true;
        }
        std::cout << "False";
        return false;
    }*/
}