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
        cm = glm::vec2(0,0);
        linearVelocity = glm::vec2(0,0);
        mass = 0.0f;
        
        std::cout << "duh fuck";
        
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
        cm = p;
    }
    glm::vec2 RigidBody::getPosition(){
        return cm;
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
    void RigidBody::setForce(glm::vec2 f) {
        force = f;
    }
    glm::vec2 RigidBody::getForce() {
        return force;
    }
    void RigidBody::step(){
        glm::vec2 p = cm;
        glm::vec2 v = linearVelocity;
        glm::vec2 f = force;
        mass = 1.0f;
        count++;
        
        std::cout << "<-----Pre Calc-------------> \n";
        std::cout << "count: " << count << "\n";
        std::cout << "rigidBodyId: " << id << "\n";
        std::cout << "pnt" << this << "\n";
        std::cout << "cm: (" << cm.x << ", " << cm.y << ")" << "\n";
        std::cout << "linVel: (" << linearVelocity.x << ", " << linearVelocity.y << ")" << "\n";
        std::cout << "pos: (" << p.x << ", " << p.y << ")" << "\n";
        std::cout << "vel: (" << v.x << ", " << v.y << ")" << "\n";
        std::cout << "force: (" << f.x << ", " << f.y << ")" << "\n";
        
        linearVelocity = v + ((f/= 2.0f)*= 16);
        cm = p + (linearVelocity);
        
        std::cout << "<----- V Calc-------------> \n";
        std::cout << "new pos: (" << cm.x << ", " << cm.y << ")" << "\n";
        std::cout << "new vel: (" << linearVelocity.x << ", " << linearVelocity.y << ")" << "\n";
        std::cout << "<-------------------------> \n";

    }
}