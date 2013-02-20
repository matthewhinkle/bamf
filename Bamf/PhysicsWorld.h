//
//  PhysicsWorld.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#ifndef __Bamf__PhysicsWorld__
#define __Bamf__PhysicsWorld__

#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "CollisionShape.h"

namespace bamf {
    
class PhysicsWorld {
public:
    PhysicsWorld(uint64_t id);
    ~PhysicsWorld();
    void setGravity(glm::vec2 g);
    void setGravity(float x, float y);
    void addObject(CollisionShape o);
    void addForce(glm::vec2 f);
    void addImpulse(glm::vec2 i);
    void addTorque(glm::vec2 t);
    void update();
protected:
    
private:
    const uint64_t id;
    glm::vec2 gravity;
    std::vector<CollisionShape> objectList;
    
    
};
}
#endif /* defined(__Bamf__PhysicsWorld__) */
