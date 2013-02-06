//
//  AudioResource.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#ifndef __Bamf__AudioResource__
#define __Bamf__AudioResource__

#include <cstdlib>
#include <cstring>
#include <string>

#include <SDL2/SDL.h>

#include "Resource.h"

namespace bamf {

class AudioResource : public Resource {
public:

	explicit AudioResource(
		uint64_t id,
		const std::string & string,
		SDL_AudioSpec audioSpec,
		uint8_t * buffer,
		uint32_t bufferLength);
	virtual ~AudioResource();
	
	inline uint64_t getId() const { return this->id; }
	inline const std::string & getName() const { return this->name; }
	
	inline SDL_AudioSpec getAudioSpec() const { return this->audioSpec; }
	inline const uint8_t * getBuffer() const { return this->buffer; }
	inline uint32_t getBufferLength() const { return this->bufferLength; }

private:
	uint64_t id;
	std::string name;
	
	SDL_AudioSpec audioSpec;
	uint8_t * buffer;
	uint32_t bufferLength;
};

}

#endif /* defined(__Bamf__AudioResource__) */
