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
    RigidBody();
    ~RigidBody();
    
    void setMass(float m);
    float getMass();
    
    void setPositon(glm::vec2 p);
    glm::vec2 getPosition();
    
    void setLinearVeloctiy(glm::vec2 v);
    glm::vec2 getLinearVeloctiy();
    
    void setAngularVelocity(float v);
    float getAngularVeloctiy();
    
    void setForce(glm::vec2 f);
    glm::vec2 getForce();
    
    void step();
    
    void update();
protected:
    
private:
    uint64_t id;
    glm::vec2 cm;
    glm::vec2 linearVelocity;
    glm::vec2 force;
    float angularVelocity;
    float mass;
    bool affectedByGravity;
    int count = 0;
};
}
#endif /* defined(__Bamf__RigidBody__) */
