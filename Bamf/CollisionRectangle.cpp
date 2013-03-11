//
//  CollisionRectangle.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionRectangle.h"
#include "CollisionCircle.h"
#include "CollisionEvent.h"
#include <math.h>

namespace bamf {
    
    uint64_t CollisionRectangle::idCounter = 0;
	
	CollisionRectangle::CollisionRectangle(const Rectangle & bounds, const glm::vec2 & hotSpot)
		:
		CollisionRectangle(glm::vec2(bounds.x, bounds.y), bounds.width, bounds.height)
	{
		this->hotSpot = hotSpot;
		this->id = nextId();
	}
    CollisionRectangle::CollisionRectangle(glm::vec2 p, float w, float h){
        position = p;
        width = w;
        height = h;
		rBody = new RigidBody();
        //std::cout << "Rect Construct - id: " << id << " hotspot: (" << hotSpot.x << ", " << hotSpot.y << ") \n";
	}
    CollisionRectangle::~CollisionRectangle() {
    }
    const glm::vec2 & CollisionRectangle::getPosition() {
        return position;
    }
    
    void CollisionRectangle::setPosition(glm::vec2 p) {
        position = p;
    }
    float CollisionRectangle::getWidth() {
        return width;
    }
    float CollisionRectangle::getHeight() {
        return height;
    }
    std::vector<glm::vec2> CollisionRectangle::getVertices() {
        std::vector<glm::vec2> vertices;
		glm::vec2 normPos = this->getPosition() - this->hotSpot;
		//bottom left
		vertices.push_back(glm::vec2(normPos.x, normPos.y));
		//top left
		vertices.push_back(glm::vec2(normPos.x , normPos.y + height));
		//top right
		vertices.push_back(glm::vec2(normPos.x + width, normPos.y + height));
		//bottom right
		vertices.push_back(glm::vec2(normPos.x + width, normPos.y));
        
        /*std::cout << "<---> \n";
        std::cout << "vert[0] (" << vertices[0].x << ", "  << vertices[0].y  << ") \n";
        std::cout << "vert[1] (" << vertices[1].x  << ", "  << vertices[1].y  << ") \n";
        std::cout << "vert[2] (" << vertices[2].x  << ", "  << vertices[2].y  << ") \n";
        std::cout << "vert[3] (" << vertices[3].x  << ", "  << vertices[3].y  << ") \n";
        std::cout << "<---> \n";*/
        
        return vertices;
    }
    
    std::vector<glm::vec2> CollisionRectangle::getAxes(std::vector<glm::vec2> verts) {
        std::vector<glm::vec2> axes;
        glm::vec2 p1;
        glm::vec2 p2;
        glm::vec2 edge;
        glm::vec2 normal;
    //v1 <-> v2 normal 
        p1 = verts[0];
        p2 = verts[1];
        edge = p1 - p2;
        normal = glm::vec2(-edge.y, edge.x);
        normal = glm::normalize(normal);
        axes.push_back(normal);
    //v2 <-> v3 normal
        p1 = verts[1];
        p2 = verts[2];
        edge = p1 - p2;
        normal = glm::vec2(-edge.y, edge.x);
        normal = glm::normalize(normal);
        axes.push_back(normal);
    //v3 <-> v4 normal
        p1 = verts[2];
        p2 = verts[3];
        edge = p1 - p2;
        normal = glm::vec2(-edge.y, edge.x);
        normal = glm::normalize(normal);        
        axes.push_back(normal);
    //v4 <-> v1 normal
        p1 = verts[3];
        p2 = verts[0];
        edge = p1 - p2;
        normal = glm::vec2(-edge.y, edge.x);
        normal = glm::normalize(normal);
        axes.push_back(normal);
        
        /*std::cout << "<---> \n";
        std::cout << "axes[0] (" << axes[0].x << ", "  << axes[0].y  << ") \n";
        std::cout << "axes[1] (" << axes[1].x  << ", "  << axes[1].y  << ") \n";
        std::cout << "axes[2] (" << axes[2].x  << ", "  << axes[2].y  << ") \n";
        std::cout << "axes[3] (" << axes[3].x  << ", "  << axes[3].y  << ") \n";
        std::cout << "<---> \n";*/
        
        return axes;
    }
    glm::vec2 CollisionRectangle::getProjection(glm::vec2 axis, std::vector<glm::vec2> verts){
        float min = glm::dot(axis, verts[0]); 
        float max = min;
        for(int i = 1; i < verts.size(); i++){
            float tmp = glm::dot(axis, verts[i]); 
            if(tmp < min) {
                min = tmp;
            }
            else if( tmp > max) {
                max = tmp;
            }
        }
        glm::vec2 proj(min,max);
        /*std::cout << "<---> \n";
        std::cout << "proj (" << proj.x  << ", "  << proj.y  << ") \n";
        std::cout << "<---> \n";*/
        return proj;
    }    
    /*bool CollisionRectangle::checkCollision(CollisionCircle c) {
		std::cout << c.getPosition().y << std::endl;
        if(c.getPosition().y <= -200){
            return true;
        }
        return false;
    }*/
    glm::vec2 CollisionRectangle::checkCollision(CollisionRectangle * r) {

        /*std::cout << "<--- checkCollision ---> \n ";
        std::cout << "<--- this ---> \n ";
        std::cout << "rBody : (" << this->getRigidBody()->getPosition().x << ", " << this->getRigidBody()->getPosition().y << ") \n";
        std::cout << "pos : (" << position.x << ", " << position.y << ") \n";
        std::cout << "hot spot : (" << hotSpot.x << ", " << hotSpot.y << ") \n";
        std::cout << "<--- r ---> \n ";
        std::cout << "rBody : (" << r->getRigidBody()->getPosition().x << ", " << r->getRigidBody()->getPosition().y << ") \n";
        std::cout << "pos : (" << r->position.x << ", " << r->position.y << ") \n";
        std::cout << "hot spot : (" << r->hotSpot.x << ", " << r->hotSpot.y << ") \n";*/

        std::vector<glm::vec2> verts1 = this->getVertices();
        std::vector<glm::vec2> verts2 = r->getVertices();
        std::vector<glm::vec2> axes1 = this->getAxes(verts1);
        std::vector<glm::vec2> axes2 = r->getAxes(verts2);
        glm::vec2 smallest(0.0f,0.0f);
        float overlap = std::numeric_limits<float>::max();
        glm::vec2 mtv(0,0);
        
        /*std:: cout << "overlap maxs: " << overlap << "\n";
        std:: cout << "verts1 \n";
        std:: cout << "verts1[0] : (" << verts1[0].x << ", " << verts1[0].y << ") \n";
        std:: cout << "verts1[1] : (" << verts1[1].x << ", " << verts1[1].y << ") \n";
        std:: cout << "verts1[2] : (" << verts1[2].x << ", " << verts1[2].y << ") \n";
        std:: cout << "verts1[3] : (" << verts1[3].x << ", " << verts1[3].y << ") \n";
        std:: cout << "--------- \n";
        std:: cout << "verts2 \n";
        std:: cout << "verts2[0] : (" << verts2[0].x << ", " << verts2[0].y << ") \n";
        std:: cout << "verts2[1] : (" << verts2[1].x << ", " << verts2[1].y << ") \n";
        std:: cout << "verts2[2] : (" << verts2[2].x << ", " << verts2[2].y << ") \n";
        std:: cout << "verts2[3] : (" << verts2[3].x << ", " << verts2[3].y << ") \n";
        std:: cout << "--------- \n";
        std:: cout << "for loop 1 \n";*/
        
        for(int i = 0; i< axes1.size(); i++) {
            glm::vec2 axis = axes1[i];
            //std:: cout << "axes1["<< i << "] : (" << axis.x << ", " << axis.y << ") \n";
            glm::vec2 proj1 = this->getProjection(axis, this->getVertices());
            glm::vec2 proj2 = r->getProjection(axis, r->getVertices());
            /*std:: cout << "proj1 : (" << proj1.x << ", " << proj1.y << ") \n";
            std:: cout << "proj2 : (" << proj2.x << ", " << proj2.y << ") \n";*/
            
            //check overlap y is the max and x is the min of the projections
            float tmpOverlap;
            if(proj1.x < proj2.x)
                tmpOverlap = proj2.x - proj1.y;
            else
                tmpOverlap = proj1.x - proj2.y;
            if(tmpOverlap > 0) {
                return glm::vec2();
            }
            else {
                if(fabs(tmpOverlap) < overlap) {
                    overlap = fabs(tmpOverlap);
                    smallest = axis;
                }
            }
        }
        
        /*std:: cout << "--------- \n";
        std:: cout << "for loop 2 \n";*/
        
        for(int i = 0; i< axes2.size(); i++) {
            glm::vec2 axis = axes2[i];
            //std:: cout << "axes2["<< i << "] : (" << axis.x << ", " << axis.y << ") \n";
            glm::vec2 proj1 = this->getProjection(axis, this->getVertices());
            glm::vec2 proj2 = r->getProjection(axis, r->getVertices());
            /*std:: cout << "proj1 : (" << proj1.x << ", " << proj1.y << ") \n";
            std:: cout << "proj2 : (" << proj2.x << ", " << proj2.y << ") \n";*/
            
        //check overlap
            float tmpOverlap;
            if(proj1.x < proj2.x)
                tmpOverlap = proj2.x - proj1.y;
            else
                tmpOverlap = proj1.x - proj2.y;
            if(tmpOverlap > 0) {
                return glm::vec2();
            }
            else {
                if(fabs(tmpOverlap) < overlap) {
                    overlap = fabs(tmpOverlap);
                    smallest = axes1[i];
                }
            }
        }
        if(verts1[0].y > verts2[0].y)
            overlap = overlap * -1;
        if(verts1[0].x < verts2[0].x)
            overlap = overlap * -1;
        mtv = smallest*overlap;
        /*std:: cout << "Small: (" << smallest.x << ", " << smallest.y << ") \n";
        std:: cout << "overlap: " << overlap << "\n";
        std:: cout << "MTV: (" << mtv.x << ", "<< mtv.y << ") \n";*/
        return mtv;
        
    }
    
    void CollisionRectangle::setIsStatic(bool s) {
        isStatic = s;
    }
    bool CollisionRectangle::getIsStatic() {
        return isStatic;
    }
    uint64_t CollisionRectangle::nextId()
    {
        return __sync_fetch_and_add(&CollisionRectangle::idCounter, 1);
    }
}