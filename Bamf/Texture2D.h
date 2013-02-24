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

#include "Resource.h"
#include "ImageResource.h"

#include "Rectangle.h"

namespace bamf {

class Texture2D : public Resource {
public:

	explicit Texture2D(uint64_t id, const ImageResource * image);
	virtual ~Texture2D();
	
	inline GLuint glTexture() const { return this->texture; }
	
	inline const ImageResource * getImage() const { return this->image; }
	inline const Rectangle & getBounds() const { return this->bounds; }
	
	void bind();
	
	/* Resource interface */
	inline uint64_t getId() const { return this->id; }
	inline const std::string & getName() const { return this->name; }
	
protected:
	/**
		Textures may be configured differently (such as a texture
		repeating when drawing beyond its bounds or not).  This
		method provides a hook for subclasses to override in order
		to customize this behavior
	 */
	virtual void configureTexture();
	
private:
	const uint64_t id;
	const std::string & name;
	const ImageResource * image;
	const Rectangle bounds;
	
	bool ready;
	GLuint texture;
	
	Texture2D(const Texture2D &);
	Texture2D & operator=(const Texture2D);
};

}

#endif /* defined(__Bamf__Texture__) */