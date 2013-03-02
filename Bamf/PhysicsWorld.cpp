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
    void PhysicsWorld::addObject(CollisionRectangle* r){
        objectList.push_back(r);
        /*std::pair<uint64_t, CollisionRectangle*> p(r->getId(),r);
        collisionSahpes.insert(p);*/
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
        for(int i = 0; i < objectList.size(); i++) {
            
            /*std::cout << "i= "<< i << " | id = " << objectList[i]->getId() << " \n";
            std::cout << "pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
            std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";
            std::cout << "width: " << objectList[i]->getWidth() << "| height: " << objectList[i]->getHeight() << "\n";*/
            for(int j = i + 1; j < objectList.size(); j++) {
                if(objectList[i]->checkCollision(objectList[j]))
                {
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
						
						jBody->setPositon(jBody->getPosition() + vnorm);
					} else {
						glm::vec2 v = jBody->getLinearVeloctiy();
						glm::vec2 vnorm = glm::normalize(-v);
						
						v.y = 0;
						v.x = 0;
						
						jBody->setLinearVeloctiy(v);
						jBody->setForce(glm::vec2());
						
						jBody->setPositon(jBody->getPosition() + vnorm);
					}
					/** end of the hax */
					
				#if 0
                    /*std::cout << "Collision Occured: i.id -  " << objectList[i].getId() << " | j.id - " << objectList[j].getId() << "\n";*/
                    objectList[i]->getRigidBody()->setForce(glm::vec2(0,0));
					
					glm::vec2 pos = objectList[i]->getRigidBody()->getPosition();
					
					//objectList[i]->getRigidBody()->setPositon(glm::vec2(pos.x, pos.y + 1));
                    objectList[i]->getRigidBody()->setLinearVeloctiy(glm::vec2(0,0));
                    objectList[j]->getRigidBody()->setForce(glm::vec2(0,0));
                    //objectList[j].getRigidBody()->setLinearVeloctiy(glm::vec2(-1,0));
				#endif
                }
             }
        }
        collisions = events;
        //std::cout << "<---- physics loop ----> \n";
        for(int i=0;i<objectList.size();i++) {
            /*std::cout << "i= "<< i << " | id = " << objectList[i]->getId() << " \n";
            std::cout << "pre step pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
            std::cout << "pre step rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";*/
            objectList[i]->getRigidBody()->step();
            objectList[i]->setPosition(objectList[i]->getRigidBody()->getPosition());

            /*std::cout << "pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
            std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";*/
        }
    }
	
	static inline bool hasZeroVelocity(RigidBody * rbody) {
		return glm::abs(glm::length(rbody->getLinearVeloctiy())) < kEpsilon;
	}
	
}
