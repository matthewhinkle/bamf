//
//  Texture2DLoader.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef __Bamf__Texture2DLoader__
#define __Bamf__Texture2DLoader__

#include <string>

#include "Paths.h"
#include "Resource.h"
#include "ResourceLoader.h"
#include "ResourceManager.h"
#include "Texture2D.h"

#include "ImageLoader.h"
#include "PngImageLoader.h"

namespace bamf {

class Texture2DLoader : public ResourceLoader {
public:

	explicit Texture2DLoader(ResourceManager & resourceManager);
	virtual ~Texture2DLoader();
	
	Resource * load(uint64_t id, const std::string & path);
	
private:
	ResourceManager & resourceManager;
	
};

}

#endif /* defined(__Bamf__Texture2DLoader__) */
