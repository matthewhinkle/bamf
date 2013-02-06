//
//  Texture2D.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#include "Texture2D.h"

namespace bamf {

Texture2D::Texture2D(uint64_t id, ImageResource * image)
{
	this->id = id;
	this->image = image;
	SDL_assert(this->image);
}

Texture2D::~Texture2D() { }

unsigned Texture2D::getWidth() const
{
	SDL_assert_paranoid(this->image);
	return this->image->getWidth();
}

unsigned Texture2D::getHeight() const
{
	SDL_assert_paranoid(this->image);
	return this->image->getHeight();
}

void Texture2D::bind()
{
	/* allocate a texture and bind it */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	
	/* only draw pixels within the bounds of the image */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
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

}