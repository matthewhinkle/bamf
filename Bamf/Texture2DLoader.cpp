//
//  Texture2DLoader.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#include "Texture2DLoader.h"

/* internal prototypes */
static inline bamf::ImageLoader * newImageLoaderFromExtension(std::string imageName);

namespace bamf {

Texture2DLoader::Texture2DLoader(ResourceManager & resourceManager)
	:
	resourceManager(resourceManager)
{ }

Texture2DLoader::~Texture2DLoader() { }

Resource * Texture2DLoader::load(uint64_t id, const std::string & path)
{
	ImageLoader * loader = newImageLoaderFromExtension(path);
	SDL_assert(loader);
	
	uint64_t imageId = resourceManager.loadResource(path, *loader);
	delete loader;
	loader = NULL;
	
	ImageResource * image = static_cast<ImageResource *>(resourceManager.getResourceById(imageId));
	SDL_assert(image);
	
	return new Texture2D(id, image);
}
	
}

static inline bamf::ImageLoader * newImageLoaderFromExtension(std::string imageName)
{
	std::transform(imageName.begin(), imageName.end(), imageName.begin(), ::tolower);
	std::string extension = bamf::Paths::getExtension(imageName);
	if(extension == "png") {
		return new bamf::PngImageLoader();
	}
	
	return NULL;
}