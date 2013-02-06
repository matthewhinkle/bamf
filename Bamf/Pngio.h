//
//  Pngio.h
//  Bamf
//
//  Updated by Matthew Hinkle on 2/1/13.
//
//

#ifndef __Bamf__Pngio__
#define __Bamf__Pngio__

/**
	@file		pngio.h
	@author		Matthew Hinkle
	@brief		libpng wrapper
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
#include <zlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* pngio_t data structure */
typedef struct pngio_t {
	png_bytep * rows;
	png_byte * image_data;
	png_uint_32 width;
	png_uint_32 height;
	png_uint_32 rowbytes;
	int bit_depth;
	int color_type;
} pngio_t;

/* intialization and cleanup */
extern int pngio_init(struct pngio_t * p);
extern int pngio_destroy(struct pngio_t * p);
extern int pngio_free(struct pngio_t * p);

/* reading */
extern int pngio_read(struct pngio_t *, const char * filename);

/* writing */
extern int pngio_write(const struct pngio_t * p, const char * filename);

/* facilitative functions */
extern int pngio_is_png(const char * filename, int * result);

/* field access */
static inline const png_byte * pngio_image_data(const struct pngio_t * p) {
	return p ? p->image_data : NULL;
}

static inline png_uint_32 pngio_width(const struct pngio_t * const p) {
	return p ? p->width : -1;
}

static inline png_uint_32 pngio_height(const struct pngio_t * const p) {
	return p ? p->height : -1;
}

static inline int pngio_bit_depth(const struct pngio_t * const p) {
	return p ? p->bit_depth : -1;
}

static inline int pngio_color_type(const struct pngio_t * const p) {
	return p ? p->color_type : -1;
}

static inline int pngio_size(const struct pngio_t * const p) {
	return p ? p->rowbytes * p->height * sizeof(png_byte) : -1;
}

#ifdef __cplusplus
}
#endif

#endif /* defined(__Bamf__Pngio__) */
