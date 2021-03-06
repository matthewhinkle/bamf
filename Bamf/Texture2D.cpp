//
//  Texture2D.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/2/13.
//
//

#include "Texture2D.h"

namespace bamf {

Texture2D::Texture2D(uint64_t id, const ImageResource * image)
	:
	id(id),
	image(image),
	name(image->getName()),
	bounds(0, 0, image->getWidth(), image->getHeight()),
	ready(false)
{ }

Texture2D::~Texture2D()
{
	if(this->ready) {
		glDeleteTextures(1, &this->texture);
		this->ready = false;
	}
}

void Texture2D::bind()
{
	if(!(this->image)) {
		return;
	}
	
	if(__sync_bool_compare_and_swap(&this->ready, false, true)) {
		/* allocate a texture and bind it */
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &this->texture);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		
		this->configureTexture();
		
		GLsizei width = static_cast<GLsizei>(this->bounds.width);
		GLsizei height = static_cast<GLsizei>(this->bounds.height);
		
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			this->image->getColorType(),
			width,
			height,
			0,
			this->image->getColorType(),
			GL_UNSIGNED_BYTE,
			this->image->getData()
		);
	} else {
		/* we just need to bind the texture */
		glBindTexture(GL_TEXTURE_2D, this->texture);
	}
}

void Texture2D::configureTexture()
{
	/* only draw pixels within the bounds of the image */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	/* use linear interpolation for resampling at different resolutions */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

}


