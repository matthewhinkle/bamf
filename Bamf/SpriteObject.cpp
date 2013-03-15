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
{ }
    
SpriteObject::SpriteObject(Sprite * sprite, u_int64_t id, bool owned)
:
sprite(sprite),
bamf::BamfObject(id, owned)
{ }

SpriteObject::~SpriteObject() { }

void SpriteObject::draw(SpriteStream * spriteStream, unsigned dt)
{
	spriteStream->begin(MatrixStack::kIdentMatrix);
	spriteStream->draw(this->sprite, this->getPosition());
	spriteStream->end();
}

}