//
//  PhysicsWorld.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "PhysicsWorld.h"
namespace bamf {
    
    PhysicsWorld::PhysicsWorld(uint64_t id)
        :
        id(id)
        {}
    
    PhysicsWorld::~PhysicsWorld(){
        
    }

    void PhysicsWorld::setGravity(glm::vec2 g){
        gravity =g;
    }
    
    void PhysicsWorld::setGravity(float x, float y){
        gravity = glm::vec2(x,y);
    }
    
    void PhysicsWorld::update(){
        //update all object in world
    }
    

    
}
