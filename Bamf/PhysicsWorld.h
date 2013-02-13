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
#include "glm/glm.hpp"
namespace bamf {
    
class PhysicsWorld {
public:
    PhysicsWorld(uint64_t id);
    ~PhysicsWorld();
    void setGravity(glm::vec2 g);
    void setGravity(float x, float y);
    void update();
protected:
    
private:
    const uint64_t id;
    glm::vec2 gravity;

    
    
};
}
#endif /* defined(__Bamf__PhysicsWorld__) */
