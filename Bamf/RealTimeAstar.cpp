//
//  RealTimeAstar.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/13/13.
//
//

#include "RealTimeAstar.h"

#include <iostream>

#include "Scene.h"

namespace bamf {

enum {
	kTimeUntilUpdate = 1500
};

static inline float cmp(Aabb<int> a, Aabb<int> b) { return a.centerDistance(b); }

RealTimeAstar::RealTimeAstar(Scene * scene, BamfObject * bamf)
	:
	scene(scene),
	navigationMesh(scene),
	pathing(false),
	timeUntilUpdate(0)
{
	this->bamf = scene->getCollisionLayer()->getObjectById(bamf->getId());
}

RealTimeAstar::~RealTimeAstar() { }

void RealTimeAstar::pathTo(NavigationStrategy * navigationStrategy, BamfObject * target)
{
	this->target = this->scene->getCollisionLayer()->getObjectById(target->getId());
	this->navigationStrategy = navigationStrategy;
	this->pathing = true;
}

void RealTimeAstar::update(Scene * scene, unsigned dt)
{
	if((timeUntilUpdate -= dt) > 0) {
		return;
	} else {
		timeUntilUpdate = kTimeUntilUpdate;
	}
	
	this->navigationMesh.computeGraph(this->navigationStrategy, this->bamf, this->target);

	if(!(this->pathing) || !(this->navigationStrategy)) return;

	const Aabb<int> & aabb = this->bamf->getAabb();
	const Aabb<int> & dest = this->navigationMesh.getDestination();
	if(aabb.intersects(dest)) {
		this->pathing = false;
		this->bamf->getRigidBody()->setLinearVeloctiy(glm::vec2());
		return;
	}
	
	std::function<float (Aabb<int>, Aabb<int>)> f(cmp);
	Astar<Aabb<int>, float, std::hash<Aabb<int>>> astar(this->navigationMesh.getGraph());
	
	std::stack<Aabb<int>> path;
	astar.search(this->navigationMesh.getStart(), this->navigationMesh.getDestination(), f, path);
	
	if(this->navigationMesh.hasClearPath(aabb, dest)) {
		glm::vec2 nextPoint = dest.center();
		glm::vec2 thisPoint = aabb.center();
		this->bamf->getRigidBody()->setLinearVeloctiy(0.6f * glm::normalize(nextPoint - thisPoint));
		return;
	}
	
	if(path.empty()) {
		this->bamf->getRigidBody()->setLinearVeloctiy(glm::vec2());
		return;
	}
	
	Aabb<int> next = path.top();
	while(next.intersects(aabb)) {
		path.pop();
		if(path.empty()) {
			break;
		}
		
		next = path.top();
		this->navigationMesh.start = next;
	}
	
	glm::vec2 nextPoint = next.center();
	glm::vec2 thisPoint = aabb.center();
	
	std::cout << "target: " << nextPoint.x << ", " << nextPoint.y << std::endl;
	
	glm::vec2 go = glm::normalize(nextPoint - thisPoint);
	
	this->bamf->getRigidBody()->setLinearVeloctiy(0.4f * go);
}

}