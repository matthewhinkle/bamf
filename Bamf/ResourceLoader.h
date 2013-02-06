//
//  ResourceLoader.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef Bamf_ResourceLoader_h
#define Bamf_ResourceLoader_h

#include <string>

namespace bamf {

class Resource;

/**
	Resource loader interface
	
	Resource loaders are used for loading in various
	types of resources (AudioResourceLoader for audio,
	ImageResourceLoader for images, etc . . .)
 */
class ResourceLoader {
public:

	explicit ResourceLoader() { }
	virtual ~ResourceLoader() { }
	
	/**
		Load the resource at the specified path and assign it
		the specified id
		
		@return the resource loaded from the specified path.
		        A return value of NULL indicates that there
				was an error loading the resource
	 */
	virtual Resource * load(uint64_t id, const std::string & path) = 0;

private:
	ResourceLoader(const ResourceLoader &);
	ResourceLoader & operator=(const ResourceLoader &);
};

}

#endif
