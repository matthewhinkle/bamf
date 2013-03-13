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
        /*std::cout << "<---- physics update ----> \n";
        std::cout << "<---- collisons loop ----> \n";*/
            
		/*std::cout << "i= "<< i << " | id = " << objectList[i]->getId() << " \n";
		std::cout << "pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
		std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";
		std::cout << "width: " << objectList[i]->getWidth() << "| height: " << objectList[i]->getHeight() << "\n";*/
        this->collisions.clear();
		scene->getCollisionLayer()->foreachPair(dt, [=](CollisionObject * a, CollisionObject * b, unsigned dt) {
			
            glm::vec2 mtv = a->getCollisionShape()->checkCollision(b->getCollisionShape());
            if(mtv != glm::vec2()){
                this->collisions.push_back(CollisionEvent(a,b,mtv));
                RigidBody * iBody = a->getRigidBody();
                RigidBody * jBody = b->getRigidBody();
                glm::vec2 v1 = iBody->getLinearVeloctiy();
                glm::vec2 v2 = jBody->getLinearVeloctiy();
                glm::vec2 n = mtv;
                n/=glm::length(mtv);
                //std::cout << "n: (" << n.x << ", " << n.y << ") \n";
                v1 *= n;
                v2 *= n;
                float recipM1 = (1/iBody->getMass());
                float recipM2 = (1/iBody->getMass());
                float e = .8;
                glm::vec2 impVec = v2-v1;
                impVec *= (e+1);
                impVec /= (recipM1 + recipM2);
                impVec *= n;
                //std::cout << "impVec: (" << impVec.x << ", " << impVec.y << ") \n";
                glm::vec2 deltaV1 = impVec/iBody->getMass();
                glm::vec2 deltaV2 = -impVec/jBody->getMass();
                if(!a->getCollisionShape()->getIsStatic()) {
                    iBody->setLinearVeloctiy(iBody->getLinearVeloctiy()+deltaV1);
					iBody->setPositon(iBody->getPosition() + mtv);
				}
                if(!b->getCollisionShape()->getIsStatic()) {
                    jBody->setLinearVeloctiy(jBody->getLinearVeloctiy()+deltaV2);
					jBody->setPositon(jBody->getPosition() + mtv);
				}
                a->getCollisionShape()->setPosition(iBody->getPosition());
                b->getCollisionShape()->setPosition(jBody->getPosition());
            }
		});
 
		scene->getCollisionLayer()->foreachObject(dt, [=](CollisionObject * collisionObject, unsigned dt) {
            if(!(collisionObject->getCollisionShape()->getIsStatic())) {
                collisionObject->getCollisionShape()->getRigidBody()->setForce(glm::vec2());
                applyForce(collisionObject->getCollisionShape()->getRigidBody() ,this->gravity);
                collisionObject->step(dt);
            }
			
		});
    }
    void PhysicsWorld::applyForce(RigidBody * rb, glm::vec2 f) {
        rb->setForce(rb->getForce() + f);
    }
	static inline bool hasZeroVelocity(RigidBody * rbody) {
		return glm::abs(glm::length(rbody->getLinearVeloctiy())) < kEpsilon;
	}
	
}
