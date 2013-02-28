//
//  BamfObject.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef Bamf_Bamf_h
#define Bamf_Bamf_h

#include <atomic>
#include <cstdint>

#include "glm/glm.hpp"

#include "Drawable.h"
#include "Updateable.h"

#include "CollisionRectangle.h"

namespace bamf {

class Scene;

/**
	First class game object
 */
class BamfObject : public Updateable, public Drawable {
public:

	explicit BamfObject(bool owned = false);
	virtual ~BamfObject();
    
	inline uint64_t getId() const { return this->id; }
	
	virtual glm::vec2 getPosition() const = 0;
	inline CollisionRectangle * getCollisionShape() const { return this->collisionShape; }
	inline RigidBody * getRigidBody() const { return this->collisionShape->getRigidBody(); }
	
	inline void setCollisionShape(CollisionRectangle * collisionShape) { this->collisionShape = collisionShape; }
	
	void update(Scene * scene, unsigned dt) { }
	void draw(SpriteStream * spriteStream, unsigned dt) { }
	
	inline bool operator<(const BamfObject & bamf) { return this->id < bamf.id; }
	
protected:
	CollisionRectangle * collisionShape;
	bool owned;

private:
	uint64_t id;

	BamfObject(const BamfObject &);
	BamfObject & operator=(const BamfObject &);
	
	static uint64_t idCounter;
	static inline uint64_t nextId();
};

}

#endif
