//
//  PngImageLoader.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#include "PngImageLoader.h"

namespace bamf {

/* internal prototypes */
static inline ColorType getColorType(int pngColorType);

PngImageLoader::PngImageLoader() { }

PngImageLoader::~PngImageLoader() { }

Resource * PngImageLoader::load(uint64_t id, const std::string & path)
{
	pngio_t pngio;
	int notinited = pngio_init(&pngio);
	SDL_assert(!(notinited));

	const char * filename = path.c_str();
	int failed = pngio_read(&pngio, filename);
	if(failed) {
		pngio_destroy(&pngio);
		return NULL;
	}
	
	Resource * resource = new ImageResource(
		id,
		path,
		const_cast<unsigned char *>(pngio_image_data(&pngio)),
		static_cast<unsigned>(pngio_size(&pngio) / sizeof(unsigned char)),
		static_cast<unsigned>(pngio_width(&pngio)),
		static_cast<unsigned>(pngio_height(&pngio)),
		pngio_bit_depth(&pngio),
		getColorType(pngio_color_type(&pngio)));
		
	pngio_destroy(&pngio);
	
	return resource;
}

static inline ColorType getColorType(int pngColorType)
{
	switch (pngColorType) {
	case PNG_COLOR_TYPE_GRAY: return COLOR_TYPE_GRAY;
	case PNG_COLOR_TYPE_GRAY_ALPHA: return COLOR_TYPE_GRAY_ALPHA;
	case PNG_COLOR_TYPE_RGB: return COLOR_TYPE_RGB;
	case PNG_COLOR_TYPE_RGB_ALPHA: return COLOR_TYPE_RGB_ALPHA;
	case PNG_COLOR_TYPE_PALETTE: return COLOR_TYPE_PALETTE;
	default: return COLOR_TYPE_UNKNOWN;
	}
}

}