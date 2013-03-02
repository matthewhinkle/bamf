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
	CollisionRectangle();
	CollisionRectangle(const Rectangle & bounds, const glm::vec2 & hotSpot = glm::vec2());
    CollisionRectangle(glm::vec2 pos, float w, float h);
    virtual ~CollisionRectangle();
    
    bool checkCollision(CollisionCircle c);
    bool checkCollision(CollisionRectangle * r);
    std::vector<glm::vec2> getVertices();
    std::vector<glm::vec2> getAxes(std::vector<glm::vec2> verts);
    glm::vec2 getProjection(glm::vec2 axis,std::vector<glm::vec2> verts);
    float getWidth();
    float getHeight();
    glm::vec2 getPosition();
    void setPosition(glm::vec2 p);
    
    inline uint64_t getId() const { return this->id; }
protected:
    
private:
    uint64_t id;
    static uint64_t idCounter;
	static inline uint64_t nextId();
	
	glm::vec2 hotSpot;
    glm::vec2 position;
    float width;
    float height;
};
}
#endif /* defined(__Bamf__CollisionRectangle__) */

