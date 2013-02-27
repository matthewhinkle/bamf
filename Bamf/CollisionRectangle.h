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
#include <vector>

namespace bamf {

class CollisionRectangle: public CollisionShape {
public:
    CollisionRectangle(glm::vec2 pos, float w, float h);
    ~CollisionRectangle();
    
    bool checkCollision(CollisionCircle c);
    bool checkCollision(CollisionRectangle r);
    std::vector<glm::vec2> getVertices();
    std::vector<glm::vec2> getAxes(std::vector<glm::vec2> verts);
    glm::vec2 getProjection(glm::vec2 axis,std::vector<glm::vec2> verts);
    
    glm::vec2 getPosition();
    void setPosition(glm::vec2 p);
    
protected:
    
private:
    
    float width;
    float height;
};
}
#endif /* defined(__Bamf__CollisionRectangle__) */

