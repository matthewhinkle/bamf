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

namespace bamf {

/**
	Static sprite class
 */
class Sprite : public Asset {
public:

	
	explicit Sprite(const Texture2D & texture, const glm::vec2 & hotspot = glm::vec2(0.0f, 0.0f));
	virtual ~Sprite();
	
	inline const Texture2D & getTexture() const { return this->texture; }
	inline const glm::vec2 & getHotspot() const { return this->hotspot; }
	inline const Rectangle & getBounds() const { return this->bounds; }
	
	/* Asset interface */
	void load(ResourceManager & resourceManager);
	bool wasLoaded() const;
	
private:
	Texture2D texture;
	const glm::vec2 hotspot;
	const Rectangle bounds;
	
	bool loaded;

	Sprite(const Sprite &);
	Sprite & operator=(const Sprite &);
};

}

#endif /* defined(__Bamf__Sprite__) */
