//
//  Drawable.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#ifndef Bamf_Drawable_h
#define Bamf_Drawable_h

#include "SpriteStream.h"

namespace bamf {

class Drawable {
public:

	Drawable() { }
	virtual ~Drawable() { }
	
	virtual void draw(SpriteStream * spriteStream, unsigned delta) = 0;
	
private:
	Drawable(const Drawable &);
	Drawable & operator=(const Drawable &);
};

}

#endif
