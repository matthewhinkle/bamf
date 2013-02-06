//
//  WavAudioLoader.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#include "WavAudioLoader.h"

namespace bamf {

WavAudioLoader::WavAudioLoader() { }

WavAudioLoader::~WavAudioLoader() { }

Resource * WavAudioLoader::load(uint64_t id, const std::string & path)
{
	SDL_AudioSpec audioSpec;
	uint8_t * buffer;
	uint32_t bufferLength;

	if(!(SDL_LoadWAV(path.c_str(), &audioSpec, &buffer, &bufferLength))) {
		return NULL;
	}
	
	Resource * resource = new AudioResource(id, path, audioSpec, buffer, bufferLength);
	
	SDL_FreeWAV(buffer);
	buffer = NULL;
	
	return resource;
}

}