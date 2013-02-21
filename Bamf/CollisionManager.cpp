//
//  CollisionManager.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionManager.h"
#include <vector>

namespace bamf {
    CollisionManager::CollisionManager(){

    }
    CollisionManager::~CollisionManager(){
        
    }
    std::vector<CollisionEvent> CollisionManager::getCollisions()
    {
        std::vector<CollisionEvent> collisions;
        //loop through all objects and check for collisions with every other object
        for(int i=0; i<objectList.size();i++){
            
            //loop through all game objects and check for collisons with object i
            for(int j=0; j<objectList.size();j++){
                //
            }
        }
        
        return collisions;
    }
}