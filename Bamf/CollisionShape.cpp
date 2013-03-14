//
//  CollisionShape.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionShape.h"
#include "RigidBody.h"


namespace bamf {
    
    CollisionShape::CollisionShape() {
        
    }
    CollisionShape::~CollisionShape() {
	
    }
    bool CollisionShape::checkCollision(CollisionShape *s){
        std::cout << "meh \n";
    }
    void CollisionShape::setRigidBody(RigidBody *r) {
        rBody = r;
    }
    RigidBody* CollisionShape::getRigidBody(){
        return rBody;
    }    
    /*void CollisionShape::setPosition(glm::vec2 p) {
        position = p;
    }
    glm::vec2 CollisionShape::getPosition() {
        return position;
    }*/
    void CollisionShape::setIsStatic(bool s) {
        isStatic = s;
    }
    bool CollisionShape::getIsStatic() {
        return isStatic;
    }
    std::string CollisionShape::getType() {
        return type;
    }
    
}