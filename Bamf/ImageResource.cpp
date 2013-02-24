//
//  ImageResource.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#include "ImageResource.h"

namespace bamf {

ImageResource::ImageResource(
		uint64_t id,
		const std::string & name,
		unsigned char * data,
		size_t dataSize,
		unsigned width,
		unsigned height,
		int bitDepth,
		ColorType colorType)
		:
		id(id),
		name(name),
		dataSize(dataSize),
		width(width),
		height(height),
		bitDepth(bitDepth),
		colorType(colorType)
{
	unsigned length = static_cast<unsigned>(dataSize / sizeof(unsigned char));
	
	SDL_assert(length > 0);
	this->data = new unsigned char[length];
	memset(this->data, 0x0, dataSize);
	
	SDL_assert(memcpy(this->data, data, dataSize));
	
	SDL_assert(colorType == kColorTypeRGB || colorType == kColorTypeRGBA);
}

ImageResource::~ImageResource()
{
	if(this->data) {
		delete[] this->data;
		this->data = NULL;
	}
}

}