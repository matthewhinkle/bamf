//
//  CollisionRectangle.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#ifndef __Bamf__CollisionRectangle__
#define __Bamf__CollisionRectangle__

#include <iostream>
#include "CollisionShape.h"
#include "Rectangle.h"
#include "CollisionCircle.h"

namespace bamf {

class CollisionRectangle: public CollisionShape {
public:
    CollisionRectangle(glm::vec2 min, glm::vec2 max);
    ~CollisionRectangle();
    bool checkCollision(CollisionCircle c);
protected:
    
private:
    glm::vec2 min;
    glm::vec2 max;
};
}
#endif /* defined(__Bamf__CollisionRectangle__) */

