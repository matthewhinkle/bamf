//
//  RigidBody.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "RigidBody.h"

namespace bamf {
    RigidBody::RigidBody(uint64_t id)
        :
        id(id)
    {}
    RigidBody::~RigidBody(){
        
    }
    
    void RigidBody::setMass(float m)
    {
        mass = m;
    }
    float RigidBody::getMass(){
        return mass;
    }
    
    void RigidBody::setPositon(glm::vec2 p){
        position = p;
    }
    glm::vec2 RigidBody::getPosition(){
        return position;
    }
    
    void RigidBody::setLinearVeloctiy(glm::vec2 v){
        linearVelocity = v;
    }
    glm::vec2 RigidBody::getLinearVeloctiy(){
        return linearVelocity;
    }
    
    void RigidBody::setAngularVelocity(float v){
        angularVelocity = v;
    }
    float RigidBody::getAngularVeloctiy(){
        return angularVelocity;
    }
    
    void RigidBody::addForce(glm::vec2 f){
        //cacluate new vel from froce
    }
    void RigidBody::addImpulse(glm::vec2 i){
        //calcualte new vel from imp
    }
    void RigidBody::addTorque(glm::vec2 t){
        //calcualte angular vel from torque
    }
    void RigidBody::update(){
        //update
    }
    
}