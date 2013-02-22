//
//  RigidBody.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "RigidBody.h"

namespace bamf {
    
    RigidBody::RigidBody()
    {
    }
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
        std::cout << "new pos x: " << p.x << "\n";
        std::cout << "new pos y: " << p.x << "\n";
        position = p;
    }
    glm::vec2 RigidBody::getPosition(){
        return position;
    }
    
    void RigidBody::setLinearVeloctiy(glm::vec2 v){
        std::cout << "new vel x: " << v.x << "\n";
        std::cout << "new vel y: " << v.x << "\n";
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
    void RigidBody::setForce(glm::vec2 f) {
        force = f;
    }
    glm::vec2 RigidBody::getForce() {
        return force;
    }
    /*void step(){
        glm::vec2 p = position;
        glm::vec2 v = linearVelocity;
        glm::vec2 f = force;
        position = p + (v *= 16);
        v = v + ((f /= s.getRigidBody().getMass()) *= 16);
        s.getRigidBody().setLinearVeloctiy(v);
        s.getRigidBody().setPositon(p);
    }*/
}