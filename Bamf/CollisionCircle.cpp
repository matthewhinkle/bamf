//
//  CollisionCircle.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionCircle.h"

namespace bamf {
    CollisionCircle::CollisionCircle(){
        
    }
    CollisionCircle::CollisionCircle(glm::vec2 p, int r){
        pos = p;
        radius = r;
    }
    CollisionCircle::~CollisionCircle(){
        
    }
    bool CollisionCircle::checkCollision(CollisionCircle c){
        glm::vec2 s = this->pos - c.pos;
        int r = ((this->radius)*(this->radius))+((c.radius)*(c.radius));
        s *=s;
        int m = ((s.x)*(s.x))+((s.y)*(s.y));
        if(m <= r)
        {
            std::cout << "True";
            return true;
        }
        std::cout << "False";
        return false;
    }
}