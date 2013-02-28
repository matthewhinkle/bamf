//
//  ObjectState.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/27/13.
//
//

#ifndef __Bamf__ObjectState__
#define __Bamf__ObjectState__

#include "RigidBody.h"
#include "CollisionRectangle.h"

namespace bamf {

struct ObjectState {
public:

	CollisionRectangle * collisionShape;

};

}

#endif /* defined(__Bamf__ObjectState__) */
