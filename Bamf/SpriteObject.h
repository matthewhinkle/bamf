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
	
	inline const glm::vec2 & getHotspot() const { return this->sprite->getHotspot(); }
	inline const Rectangle & getBounds() const { return this->sprite->getBounds(); }
	
	inline Sprite * getSprite() { return this->sprite; }

	virtual void update(Scene * scene, unsigned dt) { }
	virtual void draw(SpriteStream * spriteStream, unsigned dt);
	
private:
	Sprite * sprite;
	
	SpriteObject(const SpriteObject &);
	SpriteObject & operator=(const SpriteObject &);
};

}

#endif /* defined(__Bamf__SpriteObject__) */
