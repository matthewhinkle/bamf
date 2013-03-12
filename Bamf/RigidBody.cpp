//
//  RigidBody.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "RigidBody.h"

namespace bamf {
    
    RigidBody::RigidBody() {
        cm = glm::vec2(0,0);
        linearVelocity = glm::vec2(0,0);
        mass = 0.0f;
    }
    RigidBody::~RigidBody(){
        
    }
    void RigidBody::setMass(float m) {
        mass = m;
    }
    float RigidBody::getMass(){
        return mass;
    }
    void RigidBody::setPositon(glm::vec2 p) {
        cm = p;
    }
    const glm::vec2 & RigidBody::getPosition() {
        return cm;
    }
    void RigidBody::setLinearVeloctiy(glm::vec2 v) {
        linearVelocity = v;
    }
    glm::vec2 RigidBody::getLinearVeloctiy() {
        return linearVelocity;
    }
    void RigidBody::setAngularVelocity(float v) {
        angularVelocity = v;
    }
    float RigidBody::getAngularVeloctiy() {
        return angularVelocity;
    }
    void RigidBody::setForce(glm::vec2 f) {
        force = f;
    }
    glm::vec2 RigidBody::getForce() {
        return force;
    }
    
    bool RigidBody::isEffectedByGravity()
    {
        return this->affectedByGravity;
    }
    
    void RigidBody::setAffectedByGravity(bool isAffected)
    {
        this->affectedByGravity = isAffected;
    }
    
    void RigidBody::step(unsigned dt) {
        glm::vec2 p = cm;
        glm::vec2 pp = prevCm;
        glm::vec2 tmp = cm;
        glm::vec2 v = linearVelocity;
        glm::vec2 f = force;
        
        mass = 1.0f;
        count++;
        //r = r1 + v1 * delta t
        
        /*cm = ((p*=2) - pp) + ((f/= mass)*=(dt*dt));
        prevCm = tmp;
        linearVelocity = (cm - prevCm);
        linearVelocity /= dt;*/
        
        cm = p + (v*=dt);
        v = linearVelocity;
        linearVelocity = v + ((f/= mass)*= dt);
    }
}