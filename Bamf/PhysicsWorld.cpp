//
//  PhysicsWorld.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "PhysicsWorld.h"
namespace bamf {
    PhysicsWorld::PhysicsWorld(){
        
    }
    PhysicsWorld::~PhysicsWorld(){
        
    }
    void PhysicsWorld::setGravity(glm::vec2 g){
        gravity =g;
    }
    
    void PhysicsWorld::setGravity(float x, float y){
        gravity = glm::vec2(x,y);
    }
    void PhysicsWorld::addObject(CollisionShape o)
    {
        objectList.push_back(o);
    }
    void PhysicsWorld::update(unsigned dt){
            //meh
    }
    void PhysicsWorld::update(unsigned dt, std::vector<CollisionEvent> collisions){
        for(int i =0; i < collisions.size(); i++) {
            std::cout << "Collision: " << i << " \n";
        }
        for(int i=0;i<objectList.size();i++) {
            objectList[i].getRigidBody()->step();
        }
    }
    

    
}
