//
//  CollisionObject.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/7/13.
//
//

#include "CollisionObject.h"

namespace bamf {

CollisionObject::CollisionObject(BamfObject * bamf)
	:
	bamf::BamfObject(),
	bamf(bamf),
	collisionShape(new CollisionRectangle(bamf->getBounds(), bamf->getHotspot()))
{
	this->getCollisionShape()->setPosition(bamf->getPosition());
	this->getRigidBody()->setPositon(bamf->getPosition());
	
	this->onMoveSubscriberId = this->bamf->onMove([=](Event<BamfObject *, glm::vec2> * e) {
		const glm::vec2 position = e->getMessage();

		this->getCollisionShape()->setPosition(position);
		this->getRigidBody()->setPositon(position);
	});
}

CollisionObject::~CollisionObject()
{
	if(this->collisionShape) {
		delete this->collisionShape;
		this->collisionShape = NULL;
	}
	
	this->bamf->onMoveUnsubscribe(this->onMoveSubscriberId);
}

void CollisionObject::step(unsigned dt)
{
	RigidBody * rigidBody = this->getRigidBody();
	rigidBody->step();
	
	if(this->bamf->getPosition() != rigidBody->getPosition()) {
		this->bamf->setPosition(rigidBody->getPosition());
	}
}

}