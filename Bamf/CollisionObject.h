//
//  CollisionObject.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/7/13.
//
//

#ifndef __Bamf__CollisionObject__
#define __Bamf__CollisionObject__

#include "Aabb.h"
#include "BamfObject.h"
#include "CollisionShape.h"
#include "CollisionRectangle.h"
#include "RigidBody.h"

namespace bamf {

class CollisionObject : public BamfObject {
public:

	CollisionObject(BamfObject * bamf);
	virtual ~CollisionObject();

	inline const glm::vec2 & getPosition() const { return this->bamf->getPosition(); }
	inline const glm::vec2 & getHotspot() const { return this->bamf->getHotspot(); }
	inline const Rectangle & getBounds() const { return this->bamf->getBounds(); }
	
	inline BamfObject * getBamfObject() const { return this->bamf; }
	
	inline CollisionRectangle * getCollisionShape() const { return this->collisionShape; }
	inline RigidBody * getRigidBody() const { return this->getCollisionShape()->getRigidBody(); }
	inline Aabb<int> getAabb() const {
		return this->getAabbWithPosition(this->getPosition() - this->getHotspot());
	}
	
	inline Aabb<int> getAabbWithPosition(const glm::vec2 & position) const {
		const Rectangle & bounds = this->getBounds();
		
		return Aabb<int>(position.x, position.y, position.x + bounds.width, position.y + bounds.height);
	}

	inline void setPosition(const glm::vec2 & position) {
		this->bamf->setPosition(position);
	}
	
	void step(unsigned dt);

private:
	uint64_t onMoveSubscriberId;
	BamfObject * bamf;
	CollisionRectangle * collisionShape;

	CollisionObject(const CollisionObject &);
	CollisionObject & operator=(const CollisionObject &);
};

}

#endif /* defined(__Bamf__CollisionObject__) */
