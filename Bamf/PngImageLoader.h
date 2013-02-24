//
//  PngImageLoader.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__PngImageLoader__
#define __Bamf__PngImageLoader__

#include <iterator>
#include <istream>
#include <string>
#include <vector>

#include "png.h"

#include "SDL2/SDL.h"

#include "Resource.h"
#include "ImageLoader.h"
#include "ImageResource.h"
#include "Pngio.h"

namespace bamf {

class PngImageLoader : public ImageLoader {
public:

	PngImageLoader();
	virtual ~PngImageLoader();
	
	/* ImageLoader interface */
	Resource * load(uint64_t id, const std::string & path);
	
private:


};

}

#endif /* defined(__Bamf__PngImageLoader__) */
