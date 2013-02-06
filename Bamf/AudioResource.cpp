//
//  AudioResource.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#include "AudioResource.h"

namespace bamf {

AudioResource::AudioResource(
	uint64_t id,
	const std::string & name,
	SDL_AudioSpec audioSpec,
	uint8_t * buffer,
	uint32_t bufferLength)
{
	this->id = id;
	this->name = name;
	this->audioSpec = audioSpec;
	
	SDL_assert(bufferLength > 0);
	this->buffer = new uint8_t[bufferLength];
	memcpy(this->buffer, buffer, bufferLength * sizeof(uint8_t));
	
	this->bufferLength = bufferLength;
}

AudioResource::~AudioResource()
{
	if(this->buffer) {
		SDL_FreeWAV(this->buffer);
		this->buffer = NULL;
	}
}

}