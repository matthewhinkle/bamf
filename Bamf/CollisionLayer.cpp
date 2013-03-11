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

namespace bamf {

static inline Aabb<int> aabbFromRect(const Rectangle & rect);

CollisionLayer::CollisionLayer(Scene * scene)
	:
	SceneLayer(),
	scene(scene),
	objectById(),
	aabb(aabbFromRect(scene->getBounds())),
	qTree(aabb)
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

CollisionObject * CollisionLayer::getObjectById(uint64_t id) const
{
	std::map<uint64_t, CollisionObject *>::const_iterator i = this->objectById.find(id);
	
	return i == this->objectById.end() ? NULL : i->second;
}

CollisionObject * CollisionLayer::removeObject(uint64_t id)
{
	std::map<uint64_t, CollisionObject *>::const_iterator i = this->objectById.find(id);
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

void CollisionLayer::foreachObject(unsigned dt, const std::function<void (CollisionObject *, unsigned)> & doFunc)
{
	std::map<uint64_t, CollisionObject *>::iterator i;
	for(i = this->objectById.begin(); i != this->objectById.end(); i++) {
		doFunc(i->second, dt);
	}
}

void CollisionLayer::foreachPair(unsigned dt, const std::function<void (CollisionObject *, CollisionObject *, unsigned)> & doFunc)
{
	std::map<uint64_t, CollisionObject *>::iterator i;
	for(i = this->objectById.begin(); i != this->objectById.end(); i++) {
		std::map<uint64_t, CollisionObject *>::iterator j = i;
		
		for(++j; j != this->objectById.end(); j++) {
			doFunc(i->second, j->second, dt);
		}
	}
}

bool CollisionLayer::findObjectsIntersectingObject(BamfObject * bamf, std::vector<CollisionObject *> & objects)
{
	if(!(bamf)) return false;

	return this->findObjectsIntersectingObject(this->getObjectById(bamf->getId()), objects);
}

bool CollisionLayer::findObjectsIntersectingObject(CollisionObject * collisionObject, std::vector<CollisionObject *> & objects)
{
	if(!(collisionObject)) return false;
	
	return this->qTree.getObjectsIntersectingAabb(collisionObject->getAabb(), objects) > 0;
}

static inline Aabb<int> aabbFromRect(const Rectangle & rect) {
	return Aabb<int>(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
}

}