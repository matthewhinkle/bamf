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

namespace bamf{
    class CollisionCircle{
    public:
        CollisionCircle();
        CollisionCircle(glm::vec2 p, int r);
        ~CollisionCircle();
        bool checkCollision(CollisionCircle c);
    protected:
        
    private:
        glm::vec2 pos;
        int radius;
    };
}
#endif /* defined(__Bamf__CollisionCircle__) */
