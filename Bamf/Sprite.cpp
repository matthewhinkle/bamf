//
//  Sprite.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/5/13.
//
//

#include "Sprite.h"

namespace bamf {

Sprite::Sprite(const Texture2D & texture, const glm::vec2 & hotspot)
	:
	texture(texture),
	hotspot(hotspot),
	bounds(0, 0, texture.getWidth(), texture.getHeight()),
	loaded(false)
{ }

Sprite::~Sprite() { }

void Sprite::load(ResourceManager & resourceManager)
{
	if(!(__sync_bool_compare_and_swap(&this->loaded, false, true))) {
		/* Sprite was already loaded */
		return;
	}

	this->texture.load(resourceManager);
	SDL_assert(this->texture.wasLoaded());
}

}