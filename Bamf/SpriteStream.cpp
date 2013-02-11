//
//  SpriteStream.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/9/13.
//
//

#include "SpriteStream.h"

namespace bamf {

enum {
	kMegaByte = 1048576,
	kVboSize = 2 * kMegaByte,
	kVboStride = 0,
	kVboSpriteStride = 16,
	
	kVertexDataSize = sizeof(GLint),
	kVertexSize = 2,
	kVerticesPerSprite = 8,
	kVerticeCount = kVboSize / kVertexDataSize,
	
	kTexCoordOffset = 8 * kVertexDataSize
};

SpriteStream::SpriteStream()
{
	glGenBuffers(1, &this->vbo);	
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	
	GLint * vertices = new GLint[kVerticeCount];
	glBufferData(GL_ARRAY_BUFFER, kVboSize, vertices, GL_STREAM_DRAW);
	glVertexPointer(2, GL_INT, kVboStride, NULL);
	glTexCoordPointer(2, GL_INT, kVboStride, (void *) + (8 * sizeof(GLint)));
	
	delete[] vertices;
	vertices = NULL;
}

SpriteStream::~SpriteStream()
{
	glDeleteBuffers(1, &this->vbo);
}

SpriteStream & SpriteStream::begin(const glm::mat4 & transform)
{
	this->transform = transform;
	
	return *this;
}

SpriteStream & SpriteStream::draw(const Sprite * sprite, const glm::vec2 & position)
{
	this->sprites.insert(std::pair<const Sprite *, glm::vec3>(sprite, glm::vec3(position.x, position.y, 0.0f)));

	return *this;
}

SpriteStream & SpriteStream::end()
{
	this->flush();

	return *this;
}

void SpriteStream::flush()
{
	glBufferData(GL_ARRAY_BUFFER, kVboSize, NULL, GL_STREAM_DRAW);
	GLint * vertices = (GLint *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	
	SDL_assert(this->sprites.size() * kVboSpriteStride < kVerticeCount);
	
	std::multimap<const Sprite *, glm::vec3>::iterator i;
	std::multimap<const Sprite *, glm::vec3>::const_iterator prevSprite;
	for(prevSprite = i = this->sprites.begin(); i != this->sprites.end(); i++, vertices += kVboSpriteStride) {
		const Sprite * sprite = i->first;
	
		if(prevSprite->first < sprite) {
			/* texture swith as sprites only differ if their textures differ */
			sprite->getTexture()->bind();
		}
		
		const glm::vec3 & position = i->second;
		const Rectangle & bounds = sprite->getTexture()->getBounds();
		const Rectangle & source = sprite->getSourceRectangle();
		
		vertices[0] = position.x;
		vertices[1] = position.y;
		vertices[2] = position.x + bounds.width;
		vertices[3] = position.y;
		vertices[4] = position.x + bounds.width;
		vertices[5] = position.y + bounds.height;
		vertices[6] = position.x;
		vertices[7] = position.y + bounds.height;
		
		vertices[8] = source.x;
		vertices[9] = source.y;
		vertices[10] = source.x + source.width;
		vertices[11] = source.y;
		vertices[12] = source.x + source.width;
		vertices[13] = source.y + source.height;
		vertices[14] = source.x;
		vertices[15] = source.y + source.height;
	}
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
		
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	MatrixStack::loadMatrix(this->transform);
	
	glDrawArrays(GL_QUADS, 0, (GLsizei) (8 * this->sprites.size()));
	
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	
	MatrixStack::loadMatrix(glm::mat4());
	
	this->sprites.clear();
}

}