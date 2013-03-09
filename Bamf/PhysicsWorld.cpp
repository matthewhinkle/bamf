//
//  PhysicsWorld.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "PhysicsWorld.h"

#include <iostream>

namespace bamf {

	static const float kEpsilon = 1e-6;
	
	static inline bool hasZeroVelocity(RigidBody * rbody);
    
    PhysicsWorld::PhysicsWorld(){
        
    }
    PhysicsWorld::~PhysicsWorld(){
        
    }
    void PhysicsWorld::setGravity(glm::vec2 g){
        gravity = g;
    }
    void PhysicsWorld::setGravity(float x, float y){
        gravity = glm::vec2(x,y);
    }
    
    /*void PhysicsWorld::removeObject(uint64_t id) {
        
        collisionSahpes.erase(collisionSahpes.find(id));
        
    }*/
    
   /* CollisionRectangle* PhysicsWorld::getObject(uint64_t id) {
        return collisionSahpes[id];
    }*/
    std::vector<CollisionEvent> PhysicsWorld::getCollisions() {
        return collisions;
    }

    void PhysicsWorld::update(Scene * scene, unsigned dt){
        std::vector<CollisionEvent> events;
        /*std::cout << "<---- physics update ----> \n";
        std::cout << "<---- collisons loop ----> \n";*/
            
		/*std::cout << "i= "<< i << " | id = " << objectList[i]->getId() << " \n";
		std::cout << "pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
		std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";
		std::cout << "width: " << objectList[i]->getWidth() << "| height: " << objectList[i]->getHeight() << "\n";*/
			
		scene->getCollisionLayer()->foreachPair(dt, [=](CollisionObject * a, CollisionObject * b, unsigned dt) {
			if(!(a->getCollisionShape()->checkCollision(b->getCollisionShape()))) return;
		
			RigidBody * iBody = a->getRigidBody();
			RigidBody * jBody = b->getRigidBody();
			
			if(hasZeroVelocity(iBody) && hasZeroVelocity(jBody)) {
				return;
			} else if(hasZeroVelocity(iBody) && !(hasZeroVelocity(jBody))) {
				glm::vec2 v = jBody->getLinearVeloctiy();
				glm::vec2 vnorm = glm::normalize(-v);
				
				const glm::vec2 zero;
				jBody->setLinearVeloctiy(zero);
				jBody->setForce(zero);
				
				jBody->setPositon(jBody->getPosition() + vnorm);
			} else if(!(hasZeroVelocity(iBody) && hasZeroVelocity(jBody))) {
				glm::vec2 v = iBody->getLinearVeloctiy();
				glm::vec2 vnorm = glm::normalize(-v);
				
				const glm::vec2 zero;
				iBody->setLinearVeloctiy(zero);
				iBody->setForce(zero);
				
				iBody->setPositon(iBody->getPosition() + vnorm);
			}
		});
			
        collisions = events;
		scene->getCollisionLayer()->foreachObject(dt, [=](CollisionObject * collisionObject, unsigned dt) {
			collisionObject->step(dt);
		});
    }
	
	static inline bool hasZeroVelocity(RigidBody * rbody) {
		return glm::abs(glm::length(rbody->getLinearVeloctiy())) < kEpsilon;
	}
	
}
