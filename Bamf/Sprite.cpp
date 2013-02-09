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
	hotspot(hotspot)
{ }

Sprite::Sprite(Texture2D * texture, const glm::vec2 & hotspot)
	:
	imageName(texture->getImage()->getName()),
	texture(texture),
	hotspot(hotspot)
{ }

Sprite::~Sprite()
{
	glDeleteBuffers(2, this->vbo);
}

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

void Sprite::bind()
{
	this->texture->bind();
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
	glVertexPointer(2, GL_INT, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
	glTexCoordPointer(2, GL_INT, 0, NULL);
}

void Sprite::generateBuffers()
{
	const Rectangle & b = this->getBounds();

	GLint vertices[] = {
		0, 0,
		b.width, 0,
		b.width, b.height,
		0, b.height
	};
	
	glGenBuffers(2, this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(kDefaultTextureVertices), kDefaultTextureVertices, GL_STATIC_DRAW);
}

}