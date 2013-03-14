//
//  CollisionCircle.h
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#ifndef __Bamf__CollisionCircle__
#define __Bamf__CollisionCircle__

#include <iostream>
#include "glm.hpp"
#include "CollisionShape.h"
#include "CollisionRectangle.h"

namespace bamf {
    class CollisionCircle : public CollisionShape {
    public:
        CollisionCircle(glm::vec2 p, int r);
        //virtual ~CollisionCircle();
        bool checkCollision(CollisionShape * s);
        glm::vec2 getPosition();
        void setPosition(glm::vec2);
    protected:
        
    private:
        glm::vec2 position;
        int radius;
    };
}
#endif /* defined(__Bamf__CollisionCircle__) */
