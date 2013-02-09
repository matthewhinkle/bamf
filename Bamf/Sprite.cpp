//
//  Sprite.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/5/13.
//
//

#include "Sprite.h"

namespace bamf {

Sprite::Sprite(const std::string & imageName, const glm::vec2 & hotspot)
	:
	imageName(imageName),
	texture(NULL),
	hotspot(hotspot)
{ }

Sprite::Sprite(const Texture2D * texture, const glm::vec2 & hotspot)
	:
	imageName(texture->getImage()->getName()),
	texture(texture),
	hotspot(hotspot)
{ }

Sprite::~Sprite() { }

void Sprite::load(ResourceManager & resourceManager)
{
	if(this->texture) {
		/* texture is already loaded */
		return;
	}

	Texture2DLoader loader(resourceManager);
	uint64_t textureId = resourceManager.loadResource(this->imageName, loader);
	this->texture = static_cast<Texture2D *>(resourceManager.getResourceById(textureId));
	SDL_assert(this->texture);
}

}