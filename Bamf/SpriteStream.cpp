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

SpriteStream::SpriteStream(const Camera * camera)
	:
	camera(camera)
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

void SpriteStream::begin(const glm::mat4 & transform, int drawOptions)
{
	this->transform = transform;
	this->drawOptions = drawOptions;
}

void SpriteStream::draw(const Sprite * sprite, const glm::vec2 & position)
{
	const glm::vec2 normPos = position - sprite->getHotspot();
	if(this->drawOptions & kSpriteStreamClipEdges && this->isClipping(sprite, normPos)) {
		return;
	}
	
	if(this->drawOptions & kSpriteStreamEnforceDrawOrder) {
		this->targets.push_back(std::pair<const Sprite *, glm::vec2>(sprite, normPos));
	} else {
		this->sprites.insert(std::pair<const Sprite *, glm::vec2>(sprite, normPos));
	}
}

void SpriteStream::end()
{
	if(this->sprites.empty()) {
		return;
	}

	std::multimap<const Sprite *, glm::vec2>::const_iterator i;
	for(i = this->sprites.begin(); i != this->sprites.end(); i++) {
		this->targets.push_back(std::pair<const Sprite *, glm::vec2>(i->first, i->second));
	}
	
	this->sprites.clear();
}

void SpriteStream::flush()
{
	if(this->targets.empty()) {
		return;
	}

	SDL_assert(this->targets.size() * kVboSpriteStride < kVerticeCount);

	glBufferData(GL_ARRAY_BUFFER, kVboSize, NULL, GL_STREAM_DRAW);
	GLint * vertices = (GLint *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	
	std::vector<std::pair<const Sprite *, glm::vec2>>::iterator i;
	std::vector<std::pair<const Sprite *, glm::vec2>>::const_iterator prevSprite;
	
	/* bind the first texture */
	this->targets.begin()->first->getTexture()->bind();
	
	bamf::MatrixStack::loadMatrix(this->transform);
	for(prevSprite = i = this->targets.begin(); i != this->targets.end(); i++, vertices += kVboSpriteStride) {
		const Sprite * sprite = i->first;
	
		if(prevSprite->first != sprite) {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			this->render((i - prevSprite) * kVerticesPerSprite);
			glBufferData(GL_ARRAY_BUFFER, kVboSize, NULL, GL_STREAM_DRAW);
			vertices = (GLint *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			
			/* bind the new texture */
			sprite->getTexture()->bind();
			
			prevSprite = i;
		}
		
		const glm::vec2 & position = i->second;
		const Rectangle & bounds = sprite->getBounds();
		const Rectangle & source = sprite->getSourceRectangle();
		
		/* vertices */
		vertices[0] = position.x;
		vertices[1] = position.y;
		vertices[2] = position.x + bounds.width;
		vertices[3] = position.y;
		vertices[4] = position.x + bounds.width;
		vertices[5] = position.y + bounds.height;
		vertices[6] = position.x;
		vertices[7] = position.y + bounds.height;
		
		/* texture vertices */
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
	
	if(prevSprite->first != i->first) {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		this->render((i - prevSprite) * kVerticesPerSprite);
	}
	
	this->targets.clear();
}

void SpriteStream::render(size_t verticesCount) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(verticesCount));
	
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

}