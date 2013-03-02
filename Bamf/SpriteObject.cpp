//
//  SpriteObject.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#include "SpriteObject.h"

namespace bamf {

SpriteObject::SpriteObject(Sprite * sprite, bool owned)
	:
	sprite(sprite),
	bamf::BamfObject(owned)
{    
	this->state->collisionShape = new CollisionRectangle(sprite->getBounds(), this->sprite->getHotspot());
}

SpriteObject::~SpriteObject() { }

void SpriteObject::draw(SpriteStream * spriteStream, unsigned dt)
{
	spriteStream->begin(MatrixStack::kIdentMatrix);
	spriteStream->draw(this->sprite, this->getPosition());
	spriteStream->end();
}

}