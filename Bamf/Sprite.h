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

#include "Asset.h"
#include "Rectangle.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Texture2DLoader.h"

namespace bamf {

/**
	Static sprite class
 */
class Sprite : public Asset {
public:

	explicit Sprite(const std::string & imageName, const glm::vec2 & hotspot = glm::vec2(0.0f, 0.0f));
	explicit Sprite(const Texture2D * texture, const glm::vec2 & hotspot = glm::vec2(0.0f, 0.0f));
	virtual ~Sprite();
	
	inline const Texture2D * getTexture() const { return this->texture; }
	inline const glm::vec2 & getHotspot() const { return this->hotspot; }
	inline const Rectangle & getBounds() const { return this->texture ? this->texture->getBounds() : kNullBounds; }
	
	inline void setHotspot(const glm::vec2 & hotspot) { this->hotspot = hotspot; }
	
	/* Asset interface */
	void load(ResourceManager & resourceManager);
	inline bool wasLoaded() const { return !!(this->texture); }
	
private:
	const std::string imageName;

	const Texture2D * texture;
	glm::vec2 hotspot;
	
	static const Rectangle kNullBounds;
	
	Sprite(const Sprite &);
	Sprite & operator=(const Sprite &);
};

}

#endif /* defined(__Bamf__Sprite__) */
