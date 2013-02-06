//
//  ImageResource.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__ImageResource__
#define __Bamf__ImageResource__

#include <cstdlib>
#include <cstring>
#include <string>

#include <SDL2/SDL.h>

#include "Resource.h"

namespace bamf {

typedef enum {
	COLOR_TYPE_GRAY = 1,
	COLOR_TYPE_GRAY_ALPHA,
	COLOR_TYPE_RGB,
	COLOR_TYPE_RGB_ALPHA,
	COLOR_TYPE_PALETTE,
	COLOR_TYPE_UNKNOWN
} ColorType;

/**
	Resource class for images
 */
class ImageResource : public Resource {
public:

	explicit ImageResource(
		uint64_t id,
		const std::string & name,
		unsigned char * data,
		size_t dataSize,
		unsigned width,
		unsigned height,
		int bitDepth,
		ColorType colorType);
		
	virtual ~ImageResource();

	inline uint64_t getId() const { return this->id; }
	inline const std::string & getName() const { return this->name; }

	inline const unsigned char * getData() const { return this->data; }
	inline size_t getDataSize() const { return this->dataSize; }
	inline unsigned getWidth() const { return this->width; }
	inline unsigned getHeight() const { return this->height; }
	inline int getBitDepth() const { return this->bitDepth; }
	inline ColorType getColorType() const { return this->colorType; }

private:
	uint64_t id;
	std::string name;
	
	unsigned char * data;
	size_t dataSize;
	unsigned width;
	unsigned height;
	int bitDepth;
	ColorType colorType;
};

}

#endif /* defined(__Bamf__ImageResource__) */
