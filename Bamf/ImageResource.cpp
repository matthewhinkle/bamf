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
{
	this->id = id;
	this->name = name;
	
	unsigned length = static_cast<unsigned>(dataSize / sizeof(unsigned char));
	
	SDL_assert(length > 0);
	this->data = new unsigned char[length];
	SDL_assert(memcpy(this->data, data, dataSize));
	
	this->dataSize = dataSize;
	this->width = width;
	this->height = height;
	this->bitDepth = bitDepth;
	this->colorType = colorType;
}

ImageResource::~ImageResource()
{
	if(this->data) {
		delete[] this->data;
		this->data = NULL;
	}
}

}