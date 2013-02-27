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
    explicit CollisionShape();
    virtual ~CollisionShape();
    
    virtual bool checkCollision(CollisionShape s) {}
    
    virtual void setPosition(glm::vec2 p);
    virtual glm::vec2 getPosition();
    
    RigidBody* getRigidBody();
    void setRigidBody(RigidBody *r);
    
    inline uint64_t getId() const { return this->id; }
    
protected:
    uint64_t id;
    glm::vec2 position;
    RigidBody *rBody;
private:
    //CollisionShape(const CollisionShape &);
    //CollisionShape & operator=(const CollisionShape);
};
}
#endif /* defined(__Bamf__CollisionShape__) */
