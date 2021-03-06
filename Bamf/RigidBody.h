//
//  RigidBody.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#ifndef __Bamf__RigidBody__
#define __Bamf__RigidBody__

#include <iostream>
#include "glm.hpp"

namespace bamf {

class RigidBody{
public:
    explicit RigidBody();
    virtual ~RigidBody();
    
    void setMass(float m);
    float getMass();
    
    void setPositon(glm::vec2 p);
    const glm::vec2 & getPosition();
    
    void setLinearVeloctiy(glm::vec2 v);
    glm::vec2 getLinearVeloctiy();
    
    void setAngularVelocity(float v);
    float getAngularVeloctiy();
    
    void setForce(glm::vec2 f);
    glm::vec2 getForce();
    
    bool isEffectedByGravity();
    void setAffectedByGravity(bool isAffected);
    
    void step(unsigned dt);
    
    void update();
    
private:
    uint64_t id;
    glm::vec2 cm;
    glm::vec2 prevCm;
    glm::vec2 linearVelocity;
    glm::vec2 force;
    float angle;
    float angularVelocity;
    float mass;
    bool affectedByGravity;
};
}
#endif /* defined(__Bamf__RigidBody__) */
