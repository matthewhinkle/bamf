//
//  SpriteObject.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#include "SpriteObject.h"

namespace bamf {

SpriteObject::SpriteObject(Sprite * sprite)
	:
	sprite(sprite),
	position(0.0f, 0.0f),
	zRotation(0.0f)
{ }

SpriteObject::~SpriteObject() { }

void SpriteObject::draw(SpriteStream * spriteStream, unsigned dt)
{
	spriteStream->begin();
	spriteStream->draw(this->sprite, this->position);
	spriteStream->end();
}

}