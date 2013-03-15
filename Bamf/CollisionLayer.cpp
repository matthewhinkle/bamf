//
//  CollisionLayer.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/8/13.
//
//

#include "CollisionLayer.h"

#include "Scene.h"

#include <iostream>
#include "NavigationMesh.h"
#include "AerialNavigationStrategy.h"
#include "RealTimeAstar.h"

namespace bamf {

static inline Aabb<int> aabbFromRect(const Rectangle & rect);

CollisionLayer::CollisionLayer(Scene * scene)
	:
	scene(scene),
	objectById(),
	aabb(aabbFromRect(scene->getBounds())),
	qTree(aabb),
	realTimeAstar(NULL)
{
	this->onObjectMoveId = scene->onObjectMove([=](Event<Scene *, BamfObject *> * e) {
		CollisionObject * collisionObject = this->getObjectById(e->getMessage()->getId());
		if(collisionObject) {
			this->qTree.update(collisionObject, collisionObject->getAabb());
		}
	});

	this->onBoundsResizeId = scene->onBoundsResize([=](Event<Scene *, Rectangle> * e) {
		this->aabb = aabbFromRect(e->getMessage());
		this->qTree.resize(this->aabb);
	});
}

CollisionLayer::~CollisionLayer()
{
	for(std::pair<uint64_t, CollisionObject *> p : this->objectById) {
		if(p.second) {
			delete p.second;
			p.second = NULL;
		}
	}
	
	if(this->scene) {
		this->scene->onObjectMoveUnsubscribe(this->onObjectMoveId);
		this->scene->onBoundsResizeUnsubscribe(this->onBoundsResizeId);
	}

	this->objectById.clear();
}

void CollisionLayer::addObject(BamfObject * bamf)
{
	SDL_assert(bamf);
	
	CollisionObject * collisionObject = new CollisionObject(bamf);
	this->objectById.insert(std::pair<uint64_t, CollisionObject *>(bamf->getId(), collisionObject));
	
	this->qTree.insert(collisionObject, collisionObject->getAabb());
}

CollisionObject * CollisionLayer::getObjectById(uint64_t id)
{
	std::unordered_map<uint64_t, CollisionObject *>::const_iterator i = this->objectById.find(id);
	
	return i == this->objectById.end() ? NULL : i->second;
}

CollisionObject * CollisionLayer::removeObject(uint64_t id)
{
	std::unordered_map<uint64_t, CollisionObject *>::const_iterator i = this->objectById.find(id);
	if(i == this->objectById.end()) {
		return NULL;
	}
	
	CollisionObject * collisionObject = i->second;
	this->objectById.erase(i);
	
	if(collisionObject) {
		this->qTree.remove(collisionObject);
	}
	
	return collisionObject;
}

CollisionObject * CollisionLayer::removeObject(BamfObject * bamf)
{
	return bamf ? this->removeObject(bamf->getId()) : NULL;
}

void CollisionLayer::foreachObject(const std::function<void (CollisionObject *)> & doFunc)
{
	std::unordered_map<uint64_t, CollisionObject *>::iterator i;
	for(i = this->objectById.begin(); i != this->objectById.end(); i++) {
		doFunc(i->second);
	}
}

void CollisionLayer::foreachObject(unsigned dt, const std::function<void (CollisionObject *, unsigned)> & doFunc)
{
	std::unordered_map<uint64_t, CollisionObject *>::iterator i;
	for(i = this->objectById.begin(); i != this->objectById.end(); i++) {
		doFunc(i->second, dt);
	}
}

void CollisionLayer::foreachPair(unsigned dt, const std::function<void (CollisionObject *, CollisionObject *, unsigned)> & doFunc)
{
	std::unordered_map<uint64_t, CollisionObject *>::iterator i;
	for(i = this->objectById.begin(); i != this->objectById.end(); i++) {
		std::unordered_map<uint64_t, CollisionObject *>::iterator j = i;
		
		for(++j; j != this->objectById.end(); j++) {
			doFunc(i->second, j->second, dt);
		}
	}
}

unsigned CollisionLayer::findObjectsIntersectingLine(const Line<int> & line, std::unordered_set<CollisionObject *> & objects)
{
	return this->qTree.getObjectsIntersectingLine(line, objects);
}

unsigned CollisionLayer::findObjectsIntersectingAabb(const Aabb<int> & aabb, std::unordered_set<CollisionObject *> & objects)
{
	return this->qTree.getObjectsIntersectingAabb(aabb, objects);
}

static inline Aabb<int> aabbFromRect(const Rectangle & rect) {
	return Aabb<int>(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
}

}
