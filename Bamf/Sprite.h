//
//  Sprite.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/5/13.
//
//

#ifndef __Bamf__Sprite__
#define __Bamf__Sprite__

#include <cstdlib>
#include <cstring>

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
	
	inline Texture2D * getTexture() const { return this->texture; }
	inline const glm::vec2 & getHotspot() const { return this->hotspot; }
	inline const Rectangle & getSourceRectangle() const { return this->source; }
	
	inline void setHotspot(const glm::vec2 & hotspot) { this->hotspot = hotspot; }
	
	/* Asset interface */
	void load(ResourceManager & resourceManager);
	inline bool wasLoaded() const { return !!(this->texture); }
	
	inline bool operator<(const Sprite & s) const { return this->texture->getId() < s.texture->getId(); }
	inline bool operator==(const Sprite & s) const { return this->texture->getId() == s.texture->getId(); }
	
	friend bool operator<(const Sprite & s1, const Sprite & s2);
	friend bool operator==(const Sprite & s1, const Sprite & s2);
	
private:
	const std::string imageName;
	
	Rectangle source;

	Texture2D * texture;
	glm::vec2 hotspot;
	
	const Rectangle kNullBounds;
	
	Sprite(const Sprite &);
	Sprite & operator=(const Sprite &);
};

inline bool operator<(const Sprite & s1, const Sprite & s2) { return s1.texture->getId() < s2.texture->getId(); }
inline bool operator==(const Sprite & s1, const Sprite & s2) { return s1.texture->getId() == s2.texture->getId(); }

}

#endif /* defined(__Bamf__Sprite__) */
