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
    CollisionShape();
    virtual ~CollisionShape();
    void setRigidBody(RigidBody *r);
    virtual bool checkCollision(CollisionShape s) {}
    RigidBody* getRigidBody();
    inline uint64_t getId() const { return this->id; }
    
protected:
    
private:
    uint64_t id;
    RigidBody *rBody;
    //CollisionShape(const CollisionShape &);
   // CollisionShape & operator=(const CollisionShape);
};
}
#endif /* defined(__Bamf__CollisionShape__) */
