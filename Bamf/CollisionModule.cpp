//
//  CollisionModule.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/23/13.
//
//

#include "CollisionModule.h"
#include "CollisionRectangle.h"

namespace bamf {
    std::vector<CollisionEvent> CollisionModule::checkCollisions() {
        std::vector<CollisionEvent> collisons;
        
        /*for(int i = 0; i < collidables.size(); i++) {
            for(int j = 0; j < collidables.size(); j++) {
                if(collidables[i].checkCollision(collidables[j]))
                    collisons.push_back(CollisionEvent(collidables[i],collidables[j]));
            }
        }*/
        return collisons;
    }
    void CollisionModule::addCollidable(CollisionShape s) {
        collidables.push_back(s);
    }
    
}