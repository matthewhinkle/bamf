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
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm.hpp"
#include "CollisionShape.h"
#include "CollisionCircle.h"
#include "CollisionRectangle.h"
#include "CollisionEvent.h"
#include "CollisionObject.h"

#include "Module.h"
#include "Scene.h"

namespace bamf {
    
class PhysicsWorld : public Module {
public:
    explicit PhysicsWorld();
    virtual ~PhysicsWorld();
    void setGravity(glm::vec2 g);
    void setGravity(float x, float y);
    void removeObject(uint64_t id);
    CollisionRectangle* getObject(uint64_t id);
    void applyForce(RigidBody * rb, glm::vec2 f);
    void applyImpulse(glm::vec2 i);
    void applyTorque(glm::vec2 t);
    
    void resolveCollision(CollisionObject * a, CollisionObject * b, glm::vec2 mtv);
	
	inline void init() { }
	
    std::vector<CollisionEvent> getCollisions();
	void update(Scene * scene, unsigned dt);


protected:
    
private:
    uint64_t id;
    glm::vec2 gravity;
    std::vector<CollisionEvent> collisions;
    int timeStep = 16;
    int updateCount = 0;
};
}
#endif /* defined(__Bamf__PhysicsWorld__) */
