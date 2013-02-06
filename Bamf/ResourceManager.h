//
//  ResourceManager.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__ResourceManager__
#define __Bamf__ResourceManager__

#include <cstdlib>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "Resource.h"
#include "ResourceLoader.h"

namespace bamf {

class ResourceManager {
public:

	explicit ResourceManager();
	virtual ~ResourceManager();

	/**
		Load a resource at the specified path using the
		supplied loader
		
		@param path the path of the resource
		@param loader the loader to be used to import the
					  resource
		@return the id of the resource loaded
	 */
	uint64_t loadResource(const std::string & path, ResourceLoader & loader);
	
	/**
		Unload the resource with the specified id
		
		@param id the id of the resource to unload
	 */
	void unloadResource(uint64_t id);
	
	/**
		Unload the supplied resource
		
		@param resource the resource to unload
	 */
	void unloadResource(Resource * resource);
	
	/**
		Unload all resources being managed by this
		resource manager
	 */
	void unloadAllResources();

	/**
		Get the resource with the specified id
		
		@param id the id of the resource to get
	 */
	Resource * getResourceById(uint64_t id) const;

private:
	std::unordered_map<uint64_t, Resource *> resourceById;
	std::hash<std::string> idHashFunction;
	
	SDL_mutex * mutex;
	
	ResourceManager(const ResourceManager &);
	ResourceManager & operator=(const ResourceManager &);
};

}

#endif /* defined(__Bamf__ResourceManager__) */
