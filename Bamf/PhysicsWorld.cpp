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
<<<<<<< HEAD
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
=======
        /*std::cout << "<---- physics update ----> \n";*/
       // std::cout << "<---- collisons loop ----> \n";
        for(int i = 0; i < objectList.size(); i++) {
            
            /*std::cout << "i= "<< i << " | id = " << objectList[i]->getId() << " \n";
            std::cout << "pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
            std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";
            std::cout << "width: " << objectList[i]->getWidth() << "| height: " << objectList[i]->getHeight() << "\n";*/
            for(int j = i + 1; j < objectList.size(); j++) {
                glm::vec2 mtv = objectList[i]->checkCollision(objectList[j]);
                if(mtv != glm::vec2())
                {

                    //std::cout << "id - i :" << objectList[i]->getId() << " width: "<< objectList[i]->getWidth()<<"\n";
                    //std::cout << "id - j :" << objectList[j]->getId() << "\n";
                    events.push_back(CollisionEvent(objectList[i], objectList[j], mtv));
					//std:: cout << "mtv: (" << mtv.x << ", " << mtv.y << "\n";
                    
                    if(objectList[i]->getId() == 0)
                    {
                        objectList[i]->getRigidBody()->setLinearVeloctiy(glm::vec2());
                    }
                    else if(objectList[j]->getId() == 0) {
                        
                    }
                    /** hax hax hax, please remove the hax! :) */
					RigidBody * iBody = objectList[i]->getRigidBody();
					RigidBody * jBody = objectList[j]->getRigidBody();

					if(hasZeroVelocity(iBody) && hasZeroVelocity(jBody)) {
						continue;
					} else if(hasZeroVelocity(iBody) && !(hasZeroVelocity(jBody))) {
						glm::vec2 v = jBody->getLinearVeloctiy();
						glm::vec2 vnorm = glm::normalize(-v);
						
						v.y = 0;
						v.x = 0;
						
						jBody->setLinearVeloctiy(v);
						jBody->setForce(glm::vec2());
						
						jBody->setPositon(jBody->getPosition() + glm::normalize(vnorm));
					} else {
						glm::vec2 v = jBody->getLinearVeloctiy();
						glm::vec2 vnorm = glm::normalize(-v);
						
						v.y = 0;
						v.x = 0;
						
						jBody->setLinearVeloctiy(v);
						jBody->setForce(glm::vec2());
						
						jBody->setPositon(jBody->getPosition() + glm::normalize(vnorm));
					}
					/** end of the hax */
                }
             }
        }
        collisions = events;
        //std::cout << "<---- physics loop ----> \n";
        for(int i=0;i<objectList.size();i++) {
            /*std::cout << "i= "<< i << " | id = " << objectList[i]->getId() << " \n";
            std::cout << "pre step pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
            std::cout << "pre step rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";*/
            
            if(!objectList[i]->getIsStatic()) {
                objectList[i]->getRigidBody()->setForce(glm::vec2(0,0));
                applyForce(objectList[i]->getRigidBody(), gravity);
                
                objectList[i]->getRigidBody()->step(dt);
                //set pos of collision rectangle
            }
            
            objectList[i]->setPosition(objectList[i]->getRigidBody()->getPosition());

            /*std::cout << "pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
            std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";*/
        }

    }
	void PhysicsWorld::applyForce(RigidBody * rb, glm::vec2 f) {
        rb->setForce(rb->getForce() + f);
>>>>>>> Fixed MTV
    }
	static inline bool hasZeroVelocity(RigidBody * rbody) {
		return glm::abs(glm::length(rbody->getLinearVeloctiy())) < kEpsilon;
	}
	
}
