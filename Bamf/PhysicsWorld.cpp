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
    void PhysicsWorld::addObject(CollisionShape o)
    {
        objectList.push_back(o);
    }
    void PhysicsWorld::step(CollisionShape s){
        glm::vec2 p = s.getRigidBody().getPosition();
        glm::vec2 v = s.getRigidBody().getLinearVeloctiy();
        glm::vec2 f = s.getRigidBody().getForce();
        p = p + (v *= 16);
        v = v + ((f /= s.getRigidBody().getMass()) *= 16);
        s.getRigidBody().setLinearVeloctiy(v);
        s.getRigidBody().setPositon(p);
    }
    void PhysicsWorld::update(){
        for(int i =0;i<objectList.size();i++)
        {
            
            step(objectList[i]);
        }
    }
    

    
}
