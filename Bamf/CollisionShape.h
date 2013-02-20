//
//  CollisionShape.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#ifndef __Bamf__CollisionShape__
#define __Bamf__CollisionShape__

#include <iostream>
#include "RigidBody.h"

namespace bamf {
    
class CollisionShape {
public:
    CollisionShape(uint64_t id);
    virtual ~CollisionShape();
    virtual bool checkCollision(CollisionShape s);
    void setRigidBody(RigidBody rb);
    RigidBody getRigidBoday();
    inline uint64_t getId() const { return this->id; }
    
protected:
    
private:
    const uint64_t id;
    RigidBody rBody = RigidBody(0);
    //CollisionShape(const CollisionShape &);
    //CollisionShape & operator=(const CollisionShape);
};
}
#endif /* defined(__Bamf__CollisionShape__) */
