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

namespace bamf {
    
class CollisionShape {
public:
    CollisionShape(uint64_t id);
    virtual ~CollisionShape();
    
    inline uint64_t getId() const { return this->id; }
    
protected:
    
private:
    const uint64_t id;
    
    CollisionShape(const CollisionShape &);
    CollisionShape & operator=(const CollisionShape);
};
}
#endif /* defined(__Bamf__CollisionShape__) */
