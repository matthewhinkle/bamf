//
//  WavAudioLoader.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#ifndef __Bamf__WavAudioLoader__
#define __Bamf__WavAudioLoader__

#include <string>

#include "SDL2/SDL.h"

#include "AudioLoader.h"
#include "AudioResource.h"

namespace bamf {

class WavAudioLoader : public AudioLoader {
public:
	explicit WavAudioLoader();
	virtual ~WavAudioLoader();
	
	Resource * load(uint64_t id, const std::string & path);
};

}

#endif /* defined(__Bamf__WavAudioLoader__) */
