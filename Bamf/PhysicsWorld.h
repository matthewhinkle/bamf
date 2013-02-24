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
#include "glm.hpp"
#include "CollisionShape.h"

#include "Module.h"

namespace bamf {
    
class PhysicsWorld : public Module {
public:
    PhysicsWorld(uint64_t id);
    ~PhysicsWorld();
    void setGravity(glm::vec2 g);
    void setGravity(float x, float y);
    void addObject(CollisionShape o);
    void applyForce(glm::vec2 f);
    void applyImpulse(glm::vec2 i);
    void applyTorque(glm::vec2 t);
    //void step(CollisionShape s);
	
	inline void init() { }
	void update(unsigned dt);
protected:
    
private:
    uint64_t id;
    glm::vec2 gravity;
    std::vector<CollisionShape> objectList;
    int timeStep = 16;
    int updateCount = 0;
};
}
#endif /* defined(__Bamf__PhysicsWorld__) */
