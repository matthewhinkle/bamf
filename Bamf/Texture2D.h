//
//  Texture2D.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#ifndef __Bamf__Texture2D__
#define __Bamf__Texture2D__

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "Asset.h"
#include "ImageResource.h"
#include "ResourceManager.h"
#include "Paths.h"

#include "ImageLoader.h"
#include "PngImageLoader.h"

namespace bamf {

class Texture2D : public Asset {
public:

	explicit Texture2D(const std::string & imageName);
	Texture2D(const Texture2D & texture);
	virtual ~Texture2D();
	
	/* Asset interface */
	void load(ResourceManager & resourceManager);
	inline bool wasLoaded() const { return this->loaded; }
	
	inline GLuint glTexture() { return this->texture; }
	
	unsigned getWidth() const;
	unsigned getHeight() const;
	
	void bind();
	
private:
	const std::string imageName;
	
	ImageResource * image;
	bool loaded;
	
	GLuint texture;
};

}

#endif /* defined(__Bamf__Texture__) */