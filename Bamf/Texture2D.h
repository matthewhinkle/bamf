//
//  Texture2D.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#ifndef __Bamf__Texture2D__
#define __Bamf__Texture2D__

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Asset.h"
#include "ImageResource.h"

namespace bamf {

class Texture2D : public Asset {
public:

	explicit Texture2D(uint64_t id, ImageResource * image);
	virtual ~Texture2D();
	
	inline uint64_t getId() const { return this->id; }
	
	unsigned getWidth() const;
	unsigned getHeight() const;
	
	void bind();
	
protected:

private:
	uint64_t id;
	ImageResource * image;
	
	GLuint texture;
};

}

#endif /* defined(__Bamf__Texture__) */