//
//  ImageLoader.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__ImageLoader__
#define __Bamf__ImageLoader__

#include <string>

#include "Resource.h"
#include "ResourceLoader.h"

namespace bamf {

/**
	Loader interface for various image types;
	such as png, jpeg, tiff, etc . . .
 */
class ImageLoader : public ResourceLoader {
public:

	explicit ImageLoader() { }
	virtual ~ImageLoader() { }
	
	/* ResourceLoader interface */
	virtual Resource * load(uint64_t id, const std::string & path) = 0;
	
private:
	ImageLoader(const ImageLoader &);
	ImageLoader & operator=(const ImageLoader &);
};

}

#endif /* defined(__Bamf__ImageLoader__) */
