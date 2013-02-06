//
//  AudioLoader.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#ifndef Bamf_AudioLoader_h
#define Bamf_AudioLoader_h

#include <string>

#include "Resource.h"
#include "ResourceLoader.h"

namespace bamf {

/**
	Loader interface for various audio types
 */
class AudioLoader : public ResourceLoader {
public:

	AudioLoader() { }
	virtual ~AudioLoader() { }
	
	/* ResourceLoader interface */
	Resource * load(uint64_t id, const std::string & path) = 0;

private:
	AudioLoader(const AudioLoader &);
	AudioLoader & operator=(const AudioLoader &);
};

}

#endif
