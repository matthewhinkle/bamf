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
                this->resolveCollision(a,b,mtv);
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
    void PhysicsWorld::resolveCollision(bamf::CollisionObject *a, bamf::CollisionObject *b, glm::vec2 mtv) {
        
        RigidBody * rb1 = a->getRigidBody();
        RigidBody * rb2 = b->getRigidBody();
        glm::vec2 v1 = rb1->getLinearVeloctiy();
        glm::vec2 v2 = rb2->getLinearVeloctiy();
        
    //calculate impulse to apply to colliding objects
    //set n to unit vec in direction of mtv
        glm::vec2 n = mtv;
        n/=glm::length(mtv);
        //std::cout << "n: (" << n.x << ", " << n.y << ") \n";
        
    //multiply velocity of each rb by the unit vec n
        v1 *= n;
        v2 *= n;
        
    //set the recip of the rb's mass 
        float recipM1 = (1/rb1->getMass());
        float recipM2 = (1/rb2->getMass());
        
    //co-ef of restituion -> energy lost during collision
        float e = .5;
        
    //(v2*n)-(v1*n)    
        glm::vec2 impVec = v2-v1;
        
    //(e+1)*((v2*n)-(v1*n))     
        impVec *= (e+1);
        
    //((e+1)*((v2*n)-(v1*n)))/(1/m1 + 1/m2)    
        impVec /= (recipM1 + recipM2);
        
    //impluse vector = ((e*((v2*n)-(v1*n)))/(1/m1 + 1/m2))*n    
        impVec *= n;
        //std::cout << "impVec: (" << impVec.x << ", " << impVec.y << ") \n";
        
    //calc change in veloctiy for both objects p/m
        glm::vec2 deltaV1 = impVec/rb1->getMass();
        glm::vec2 deltaV2 = -impVec/rb2->getMass();
        
    //if objects are not static apply the impulse/change of velocity
        if(!a->getCollisionShape()->getIsStatic()) {
            rb1->setLinearVeloctiy(rb1->getLinearVeloctiy()+deltaV1);
            rb1->setPositon(rb1->getPosition() + mtv);
        }
        if(!b->getCollisionShape()->getIsStatic()) {
            rb2->setLinearVeloctiy(rb2->getLinearVeloctiy()+deltaV2);
            rb2->setPositon(rb2->getPosition() - mtv);
        }
        a->getCollisionShape()->setPosition(rb1->getPosition());
        b->getCollisionShape()->setPosition(rb2->getPosition());
    }
    void PhysicsWorld::applyForce(RigidBody * rb, glm::vec2 f) {
        rb->setForce(rb->getForce() + f);
    }
	static inline bool hasZeroVelocity(RigidBody * rbody) {
		return glm::abs(glm::length(rbody->getLinearVeloctiy())) < kEpsilon;
	}
	
}
