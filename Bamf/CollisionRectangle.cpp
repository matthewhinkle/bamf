//
//  CollisionRectangle.cpp
//  Bamf
//
//  Created by Anthony Dagostino on 2/11/13.
//
//

#include "CollisionRectangle.h"
#include "CollisionCircle.h"

namespace bamf {
    
    uint64_t CollisionRectangle::idCounter = 0;
    
    CollisionRectangle::CollisionRectangle(glm::vec2 pos, float w, float h){
        position = pos;
        width = w;
        height = h;
	}
    
    CollisionRectangle::~CollisionRectangle() {
        id = nextId();
    }
    
    glm::vec2 CollisionRectangle::getPosition() {
        return position;
    }
    
    void CollisionRectangle::setPosition(glm::vec2 p) {
        position = p;
    }
    
    std::vector<glm::vec2> CollisionRectangle::getVertices() {
        std::vector<glm::vec2> vertices;
        //add v1 - bottom left vertex
        vertices.push_back(glm::vec2(position.x - (width/2.0f), position.y - (height/2.0f)));
        //add v2 - top right vertex
        vertices.push_back(glm::vec2(position.x - (width/2.0f), position.y + (height/2.0f)));
        //add v3 - top left vertex
        vertices.push_back(glm::vec2(position.x + (width/2.0f), position.y + (height/2.0f)));
        //add v4 - bottom right vertex
        vertices.push_back(glm::vec2(position.x + (width/2.0f), position.y - (height/2.0f)));
        
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
        axes.push_back(normal);
    //v2 <-> v3 normal
        p1 = verts[1];
        p2 = verts[2];
        edge = p1 - p2;
        normal = glm::vec2(-edge.y, edge.x);
        axes.push_back(normal);
    //v3 <-> v4 normal
        p1 = verts[2];
        p2 = verts[3];
        edge = p1 - p2;
        normal = glm::vec2(-edge.y, edge.x);
        axes.push_back(normal);
    //v4 <-> v1 normal
        p1 = verts[3];
        p2 = verts[0];
        edge = p1 - p2;
        normal = glm::vec2(-edge.y, edge.x);
        axes.push_back(normal);
        
        return axes;
    }
    glm::vec2 CollisionRectangle::getProjection(glm::vec2 axis, std::vector<glm::vec2> verts){
        //min is the dot product between axis and vertex 0 
        float min = (((axis.x)*(verts[0].x))+((axis.y)*(verts[0].y)));
        float max = min;
        for(int i = 1; i < verts.size(); i++){
            //tmp is the dot product between axis and vertex i 
            float tmp = (((axis.x)*(verts[i].x))+((axis.y)*(verts[i].y)));
            if(tmp < min) {
                min = tmp;
            }
            else if( tmp > max) {
                max = tmp;
            }
        }
        glm::vec2 proj(min,max);
        return proj;
    }    
    /*bool CollisionRectangle::checkCollision(CollisionCircle c) {
		std::cout << c.getPosition().y << std::endl;
        if(c.getPosition().y <= -200){
            return true;
        }
        return false;
    }*/
    bool CollisionRectangle::checkCollision(CollisionRectangle * r) {
        std::vector<glm::vec2> verts1 = this->getVertices();
        std::vector<glm::vec2> verts2 = r->getVertices();
        std::vector<glm::vec2> axes1 = this->getAxes(verts1);
        std::vector<glm::vec2> axes2 = r->getAxes(verts2);
        /*std:: cout << "verts1 \n";
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
            //std:: cout << "proj1 : (" << proj1.x << ", " << proj1.y << ") \n";
            //std:: cout << "proj2 : (" << proj2.x << ", " << proj2.y << ") \n";
            //check overlap y is the max and x is the min of the projections
            if(!(proj1.y>=proj2.x)) {
                //std:: cout << "return false \n";
                return false;
            }
        }
        
        //std:: cout << "--------- \n";
        //std:: cout << "for loop 2 \n";
        
        for(int i = 0; i< axes2.size(); i++) {
            glm::vec2 axis = axes2[i];
            //std:: cout << "axes2["<< i << "] : (" << axis.x << ", " << axis.y << ") \n";
            glm::vec2 proj1 = this->getProjection(axis, this->getVertices());
            glm::vec2 proj2 = r->getProjection(axis, r->getVertices());
            //std:: cout << "proj1 : (" << proj1.x << ", " << proj1.y << ") \n";
            //std:: cout << "proj2 : (" << proj2.x << ", " << proj2.y << ") \n";
            //check overlap
            if(!(proj1.y>=proj2.x)) {
                //std:: cout << "return false \n";
                return false;
            }
        }
        //std:: cout << "return true \n";
        return true;
    }
    
    uint64_t CollisionRectangle::nextId()
    {
        return __sync_fetch_and_add(&CollisionRectangle::idCounter, 1);
    }
}