//
//  Sprite.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/5/13.
//
//

#include "Sprite.h"

/* constants */
static const GLint kDefaultTextureVertices[] = {
	0, 0,
	1, 0,
	1, 1,
	0, 1
};

namespace bamf {

Sprite::Sprite(const std::string & imageName, const glm::vec2 & hotspot)
	:
	imageName(imageName),
	texture(NULL),
	hotspot(hotspot),
	source()
{ }

Sprite::Sprite(Texture2D * texture, const glm::vec2 & hotspot)
	:
	imageName(texture->getImage()->getName()),
	texture(texture),
	hotspot(hotspot),
	source(texture->getBounds())
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
	
	const Rectangle & r = this->texture->getBounds();
	this->source = Rectangle(
		r.x / r.width,
		r.y / r.height,
		1,
		1
	);
}

}