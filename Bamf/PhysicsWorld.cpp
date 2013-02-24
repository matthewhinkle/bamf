//
//  PhysicsWorld.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/13/13.
//
//

#include "PhysicsWorld.h"
namespace bamf {
    
    PhysicsWorld::PhysicsWorld(uint64_t id)
        :
        id(id)
        {}
    
    PhysicsWorld::~PhysicsWorld(){
        
    }

    void PhysicsWorld::setGravity(glm::vec2 g){
        gravity =g;
    }
    
    void PhysicsWorld::setGravity(float x, float y){
        gravity = glm::vec2(x,y);
    }
    void PhysicsWorld::addObject(CollisionShape o)
    {
        objectList.push_back(o);
    }
    /*void PhysicsWorld::step(CollisionShape s){
        glm::vec2 p = s.getRigidBody().getPosition();
        glm::vec2 v = s.getRigidBody().getLinearVeloctiy();
        glm::vec2 f = s.getRigidBody().getForce();
        s.getRigidBody().setMass(1.0f);
        std::cout << "<-----Pre Calc-------------> \n";
        std::cout << "pos: (" << p.x << ", " << p.y << ")" << "\n";
        std::cout << "vel: (" << v.x << ", " << v.y << ")" << "\n";
        std::cout << "force: (" << f.x << ", " << f.y << ")" << "\n";
        glm::vec2 tmp =v;
        tmp*=16;
        std::cout << "tmp pos: (" << tmp.x << ", " << tmp.y << ")" << "\n";
        p = p + (tmp);
        std::cout << "<-----V Calc-------------> \n";
        v = v + ((f /= 1.0f) *= 16);
        
        std::cout << "new pos: (" << p.x << ", " << p.y << ")" << "\n";
        std::cout << "new vel: (" << v.x << ", " << v.y << ")" << "\n";
        
        s.getRigidBody().setLinearVeloctiy(v);
        s.getRigidBody().setPositon(p);
        
    }*/
    void PhysicsWorld::update(){
        for(int i=0;i<objectList.size();i++)
        {
            objectList[i].getRigidBody()->step();
            std::cout << "i: " << i << "\n";
            updateCount++;
            
        }
        std::cout << "update: " << updateCount << "\n";
    }
    

    
}
