//
//  SpriteObject.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#ifndef __Bamf__SpriteObject__
#define __Bamf__SpriteObject__

#include "glm/glm.hpp"

#include "BamfObject.h"
#include "Sprite.h"
#include "SpriteStream.h"

namespace bamf {

class SpriteObject : public BamfObject {
public:

	explicit SpriteObject(Sprite * sprite, bool owned = false);
	virtual ~SpriteObject();
	
	inline glm::vec2 getPosition() const { return this->state->collisionShape->getRigidBody()->getPosition(); }
	
	inline Sprite * getSprite() { return this->sprite; }
	
	inline void setPosition(const glm::vec2 & position) {
		this->state->collisionShape->getRigidBody()->setPositon(position);
	}

	virtual void update(Scene * scene, unsigned dt) { }
	virtual void draw(SpriteStream * spriteStream, unsigned dt);
	
private:
	Sprite * sprite;
	
	SpriteObject(const SpriteObject &);
	SpriteObject & operator=(const SpriteObject &);
};

}

#endif /* defined(__Bamf__SpriteObject__) */
