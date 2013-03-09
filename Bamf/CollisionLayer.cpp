//
//  CollisionLayer.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/8/13.
//
//

#include "CollisionLayer.h"

namespace bamf {

CollisionLayer::CollisionLayer()
	:
	SceneLayer(),
	objectById()
{ }

CollisionLayer::~CollisionLayer()
{
	this->objectById.clear();
}

void CollisionLayer::addObject(CollisionObject * collisionObject)
{
	SDL_assert(collisionObject);

	const BamfObject * const object = collisionObject->getBamfObject();
	SDL_assert(object);
	
	this->objectById.insert(std::pair<uint64_t, CollisionObject *>(object->getId(), collisionObject));
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
	
	return collisionObject;
}

CollisionObject * CollisionLayer::removeObject(CollisionObject * collisionObject)
{
	return collisionObject && collisionObject->getBamfObject() ? this->removeObject(collisionObject->getBamfObject()->getId()) : NULL;
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

}