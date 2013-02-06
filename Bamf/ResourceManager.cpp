//
//  ResourceManager.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#include "ResourceManager.h"

namespace bamf {

ResourceManager::ResourceManager()
{
	this->mutex = SDL_CreateMutex();
}

ResourceManager::~ResourceManager()
{
	this->unloadAllResources();
	this->resourceById.clear();
	SDL_DestroyMutex(this->mutex);
	this->mutex = NULL;
}

uint64_t ResourceManager::loadResource(const std::string & path, bamf::ResourceLoader & loader)
{
	SDL_mutexP(this->mutex);
	size_t id = this->idHashFunction(path);
	std::unordered_map<uint64_t, Resource *>::const_iterator i = this->resourceById.find(id);
	if(i == this->resourceById.end()) {
		/* resource must be loaded */
		Resource * resource = loader.load(id, path);
		SDL_assert(resource);
	
		this->resourceById[id] = resource;
	}
	SDL_mutexV(this->mutex);
	
	return id;
}

void ResourceManager::unloadResource(uint64_t id)
{
	SDL_mutexP(this->mutex);
	std::unordered_map<uint64_t, Resource *>::iterator i = this->resourceById.find(id);
	if(i != this->resourceById.end()) {
		/* the resource exists */
		Resource * resource = i->second;
		if(resource) {
			delete resource;
			resource = NULL;
		}
		
		this->resourceById.erase(i);
	}
	SDL_mutexV(this->mutex);
}

void ResourceManager::unloadAllResources()
{
	SDL_mutexP(this->mutex);
	std::unordered_map<uint64_t, Resource *>::iterator i = this->resourceById.begin();
	for(i = this->resourceById.begin(); i != this->resourceById.end(); i++) {
		Resource * resource = i->second;
		if(resource) {
			delete resource;
			resource = NULL;
		}
		
		this->resourceById.erase(i);
	}
	SDL_mutexV(this->mutex);
}

Resource * ResourceManager::getResourceById(uint64_t id) const
{
	std::unordered_map<uint64_t, Resource *>::const_iterator i = this->resourceById.find(id);
	if(i == this->resourceById.end()) {
		return NULL;
	}
	
	return i->second;
}

}