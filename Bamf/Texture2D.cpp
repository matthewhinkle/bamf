//
//  Texture2D.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#include "Texture2D.h"

/* internal prototypes */
static inline bamf::ImageLoader * newImageLoaderFromExtension(std::string imageName);

namespace bamf {

Texture2D::Texture2D(const std::string & imageName)
	:
	imageName(imageName),
	image(NULL),
	loaded(false)
{ }

Texture2D::Texture2D(const Texture2D & texture)
	:
	imageName(texture.imageName),
	image(texture.image),
	loaded(texture.loaded),
	texture(texture.texture)
{ }

Texture2D::~Texture2D() { }

unsigned Texture2D::getWidth() const
{
	return this->image ? this->image->getWidth() : 0;
}

unsigned Texture2D::getHeight() const
{
	SDL_assert_paranoid(this->image);
	return this->image ? this->image->getHeight() : 0;
}

void Texture2D::bind()
{
	if(!(this->image)) {
		return;
	}

	/* allocate a texture and bind it */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	
	/* only draw pixels within the bounds of the image */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	/* use linear interpolation for resampling at different resolutions */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	GLsizei width = static_cast<GLsizei>(this->getWidth());
	GLsizei height = static_cast<GLsizei>(this->getHeight());
	
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		this->image->getData()
	);
}

void Texture2D::load(ResourceManager & resourceManager)
{
	if(!(__sync_bool_compare_and_swap(&this->loaded, false, true))) {
		/* texture was already loaded */
		return;
	}
	
	ImageLoader * loader = newImageLoaderFromExtension(this->imageName);
	SDL_assert(loader);
	
	uint64_t imageId = resourceManager.loadResource(this->imageName, *loader);
	delete loader;
	loader = NULL;
	
	this->image = static_cast<ImageResource *>(resourceManager.getResourceById(imageId));
	SDL_assert(this->image);	
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
