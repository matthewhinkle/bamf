//
//  SpriteObject.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#include "SpriteObject.h"

namespace bamf {

SpriteObject::SpriteObject(Sprite * sprite, RigidBody * rigidBody)
	:
	sprite(sprite),
	zRotation(0.0f),
	rigidBody(rigidBody)
{ }

SpriteObject::~SpriteObject() { }

void SpriteObject::draw(SpriteStream * spriteStream, unsigned dt)
{
	spriteStream->begin();
	spriteStream->draw(this->sprite, this->getPosition());
	spriteStream->end();
}

}