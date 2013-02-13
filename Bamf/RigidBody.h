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
    RigidBody(uint64_t id);
    ~RigidBody();
    
    void setMass(float m);
    float getMass();
    
    void setPositon(glm::vec2 p);
    glm::vec2 getPosition();
    
    void setLinearVeloctiy(glm::vec2 v);
    glm::vec2 getLinearVeloctiy();
    
    void setAngularVelocity(float v);
    float getAngularVeloctiy();
    
    void addForce(glm::vec2 f);
    void addImpulse(glm::vec2 i);
    void addTorque(glm::vec2 t);
    
    void update();
    
protected:
    
private:
    const uint64_t id;
    uint64_t worldId;
    glm::vec2 position;
    glm::vec2 linearVelocity;
    float angularVelocity;
    float mass;
    bool affectedByGravity;
    
};
}
#endif /* defined(__Bamf__RigidBody__) */
