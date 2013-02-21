//
//  CollisionShape.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionShape.h"

namespace bamf {
    CollisionShape::CollisionShape()
    {}
    CollisionShape::~CollisionShape(){
        
    }
    void CollisionShape::setRigidBody(RigidBody r){
        rBody = r;
    }
    RigidBody CollisionShape::getRigidBody(){
        return rBody;
    }
    bool CollisionShape::checkCollision(CollisionShape s){
        return false;
    }
    
}