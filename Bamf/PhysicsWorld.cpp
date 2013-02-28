//
//  PhysicsWorld.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "PhysicsWorld.h"
namespace bamf {
    
    PhysicsWorld::PhysicsWorld(){
        
    }
    PhysicsWorld::~PhysicsWorld(){
        
    }
    void PhysicsWorld::setGravity(glm::vec2 g){
        gravity =g;
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
            std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";*/
            for(int j = 0; j < objectList.size(); j++) {
               if(j != i) {
                if(objectList[i]->checkCollision(objectList[j]))
                {
                    /*std::cout << "Collision Occured: i.id -  " << objectList[i].getId() << " | j.id - " << objectList[j].getId() << "\n";*/
                    objectList[i]->getRigidBody()->setForce(glm::vec2(0,0));
                    objectList[i]->getRigidBody()->setLinearVeloctiy(glm::vec2(0,0));
                    objectList[j]->getRigidBody()->setForce(glm::vec2(0,0));
                    //objectList[j].getRigidBody()->setLinearVeloctiy(glm::vec2(-1,0));
                }
               }
             }
        }
        collisions = events;
        //std::cout << "<---- physics loop ----> \n";
        for(int i=0;i<objectList.size();i++) {
            /*std::cout << "i= "<< i << " | id = " << objectList[i]->getId() << " \n";
            std::cout << "pos: (" << objectList[i]->getPosition().x << ", " << objectList[i]->getPosition().y << " )\n";
            std::cout << "rigid body pos: (" << objectList[i]->getRigidBody()->getPosition().x << ", " << objectList[i]->getRigidBody()->getPosition().y << " )\n";*/
            objectList[i]->getRigidBody()->step();
            objectList[i]->setPosition(objectList[i]->getRigidBody()->getPosition());
        }
    }
}
