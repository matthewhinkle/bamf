//
//  Sprite.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/5/13.
//
//

#ifndef __Bamf__Sprite__
#define __Bamf__Sprite__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Asset.h"
#include "Rectangle.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Texture2DLoader.h"

namespace bamf {

enum {
	kSpriteVerticesBuffer = 0,
	kSpriteTextureVerticesBuffer = 1,
	kSpriteVertexBufferCount = 2,
	kSpriteVecticesDrawn = 4,
	kSpriteVerticesCount = 8
};

/**
	Static sprite class
 */
class Sprite : public Asset {
public:

	explicit Sprite(const std::string & imageName, const glm::vec2 & hotspot = glm::vec2(0.0f, 0.0f));
	explicit Sprite(Texture2D * texture, const glm::vec2 & hotspot = glm::vec2(0.0f, 0.0f));
	virtual ~Sprite();
	
	inline const Texture2D * getTexture() const { return this->texture; }
	inline const glm::vec2 & getHotspot() const { return this->hotspot; }
	inline const Rectangle getBounds() const { return this->texture ? this->texture->getBounds() : kNullBounds; }
	
	inline void setHotspot(const glm::vec2 & hotspot) { this->hotspot = hotspot; }
	
	/**
		Bind the sprite's vertex buffers to prepare for
		drawing
	 */
	virtual void bind();
	virtual void generateBuffers();
	
	inline virtual GLsizei getVertexCount() { return 4; }
	
	/* Asset interface */
	void load(ResourceManager & resourceManager);
	inline bool wasLoaded() const { return !!(this->texture); }
	
private:
	const std::string imageName;
	
	GLuint vbo[kSpriteVertexBufferCount];

	Texture2D * texture;
	glm::vec2 hotspot;
	
	const Rectangle kNullBounds;
	
	Sprite(const Sprite &);
	Sprite & operator=(const Sprite &);
};

}

#endif /* defined(__Bamf__Sprite__) */
