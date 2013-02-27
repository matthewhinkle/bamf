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

	explicit SpriteObject(Sprite * sprite, CollisionRectangle * collisionShape = NULL);
	virtual ~SpriteObject();
	
	inline glm::vec2 getPosition() const { return this->collisionShape->getRigidBody()->getPosition(); }
	
	inline Sprite * getSprite() { return this->sprite; }

	void update(unsigned dt) { }

	void draw(SpriteStream * spriteStream, unsigned dt);
	
private:
	Sprite * sprite;
	
	SpriteObject(const SpriteObject &);
	SpriteObject & operator=(const SpriteObject &);
};

}

#endif /* defined(__Bamf__SpriteObject__) */
