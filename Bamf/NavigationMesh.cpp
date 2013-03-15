//
//  NavigationMesh.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/9/13.
//
//

#include "NavigationMesh.h"

#include "Scene.h"

namespace bamf {

NavigationMesh::NavigationMesh(Scene * scene)
	:
	scene(scene),
	graph()
{ }

NavigationMesh::~NavigationMesh() { }

void NavigationMesh::computeGraph(NavigationStrategy * navigationStrategy, CollisionObject * src, CollisionObject * dst)
{
	this->graph.clear();
	CollisionLayer * collisionLayer = this->scene->getCollisionLayer();
	
	this->src = src;
	this->dst = dst;
	
	this->start = src->getAabb();
	this->destination = dst->getAabb();
	
	this->navigate(navigationStrategy, src);
	this->navigate(navigationStrategy, dst);
	collisionLayer->foreachObject([=](CollisionObject * collisionObject) {
		this->navigate(navigationStrategy, collisionObject);
	});
}

void NavigationMesh::navigate(NavigationStrategy * navigationStrategy, CollisionObject * collisionObject) {
	std::vector<Aabb<int>> aabbs;
	
	if(collisionObject == this->src) {
		aabbs.push_back(this->start);
	} else if(collisionObject == this->dst) {
		aabbs.push_back(this->destination);
	} else {
		this->getAabbs(collisionObject->getAabb(), aabbs);
	}
	
	std::unordered_set<CollisionObject *> potentialNeighbors;
	navigationStrategy->discoverPotentialNeighbors(collisionObject, src, potentialNeighbors);
	
	for(const Aabb<int> & aabb : aabbs) {
		if(this->objectsCollideWithAabb(aabb)) {
			continue;
		}
	
		for(CollisionObject * potentialNeighbor : potentialNeighbors) {
			std::vector<Aabb<int>> potentialAabbs;
			this->getAabbs(potentialNeighbor->getAabb(), potentialAabbs);
			
			for(const Aabb<int> & potentialAabb : potentialAabbs) {
				if(this->objectsCollideWithAabb(potentialAabb) || !(this->hasClearPath(aabb, potentialAabb))) {
					continue;
				}
				
				this->graph.addEdge(aabb, potentialAabb, aabb.centerDistance(potentialAabb));
			}
		}
		
		if(!(this->objectsCollideWithAabb(this->destination)) && this->hasClearPath(aabb, this->destination)) {
			this->graph.addEdge(aabb, this->destination, aabb.centerDistance(this->destination));
		}
	}
}

void NavigationMesh::getAabbs(const Aabb<int> & a, std::vector<Aabb<int>> & aabbs)
{
	const Rectangle & b = this->src->getBounds();

	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMin, a.yMax + 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMax - b.width, a.yMax + 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMin, a.yMin - b.height - 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMax - b.width, a.yMin - b.height - 1)));
	
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMax + 1, a.yMin)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMin - 1, a.yMin)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMax + 1, a.yMax)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMin - 1, a.yMax)));
	
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMax + 1, a.yMax + 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMax + 1, a.yMin - 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMin - b.width - 1, a.yMin - 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMin - b.width - 1, a.yMax + 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMax + 1, a.yMax - b.height - 1)));
	aabbs.push_back(this->src->getAabbWithPosition(glm::vec2(a.xMin - 1, a.yMax - b.height - 1)));
}

bool NavigationMesh::objectsCollideWithAabb(const Aabb<int> & aabb)
{
	CollisionLayer * collisonLayer = this->scene->getCollisionLayer();
	std::unordered_set<CollisionObject *> objects;
	collisonLayer->findObjectsIntersectingAabb(aabb, objects);

	objects.erase(this->src);
	objects.erase(this->dst);
	
	return !(objects.empty());
}

bool NavigationMesh::hasClearPath(const Aabb<int> & src, const Aabb<int> & dst)
{
	Line<int> top;
	Line<int> bottom;
	
	if(src.xMin > dst.xMin) {
		if(src.yMin < dst.yMin) {
			top = Line<int>(src.xMax, src.yMax, dst.xMax,dst.yMax);
			bottom = Line<int>(src.xMin, src.yMin, dst.xMin, dst.yMin + 1);
		} else {
			top = Line<int>(src.xMin, src.yMax, dst.xMax,dst.yMax);
			bottom = Line<int>(src.xMax, src.yMin, dst.xMin, dst.yMin + 1);
		}
	} else {
		if(src.yMin < dst.yMin) {
			top = Line<int>(src.xMin, src.yMax, dst.xMin, dst.yMax);
			bottom = Line<int>(src.xMax, src.yMin, dst.xMin, dst.yMin + 1);
		} else {
			top = Line<int>(src.xMax, src.yMax, dst.xMin, dst.yMax);
			bottom = Line<int>(src.xMin, src.yMin, dst.xMin, dst.yMin + 1);
		}
	}
	
	CollisionLayer * collisionLayer = this->scene->getCollisionLayer();
	
	std::unordered_set<CollisionObject *> objects;
	collisionLayer->findObjectsIntersectingLine(top, objects);
	collisionLayer->findObjectsIntersectingLine(bottom, objects);
	objects.erase(this->src);
	objects.erase(this->dst);
	
	return objects.empty();
}

}