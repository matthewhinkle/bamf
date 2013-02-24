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

	explicit SpriteObject(Sprite * sprite);
	virtual ~SpriteObject();
	
	inline const glm::vec2 & getPosition() const { return this->position; }
	inline float getZRotation() const { return this->zRotation; }
	
	inline void setPosition(const glm::vec2 & position) { this->position = position; }
	inline void setZRotation(float zRotation) { this->zRotation = zRotation; }
	
	inline Sprite * getSprite() { return this->sprite; }

	void update(unsigned dt) { }

	void draw(SpriteStream * spriteStream, unsigned dt);
private:
	Sprite * sprite;
	
	glm::vec2 position;
	float zRotation;
	
	SpriteObject(const SpriteObject &);
	SpriteObject & operator=(const SpriteObject &);
};

}

#endif /* defined(__Bamf__SpriteObject__) */
