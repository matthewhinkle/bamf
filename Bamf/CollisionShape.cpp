//
//  CollisionShape.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionShape.h"

namespace bamf {

CollisionShape::CollisionShape(uint64_t id)
    :
    id(id)
{}
    
CollisionShape::~CollisionShape()
{
        
}

bool CollisionShape::checkCollision(CollisionShape s){
    return false;
}
    
}