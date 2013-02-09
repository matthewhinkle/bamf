//
//  SpriteStream.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/9/13.
//
//

#ifndef __Bamf__SpriteStream__
#define __Bamf__SpriteStream__

#include "SDL2/SDL_opengl.h"

#include "glm/glm.hpp"

#include "MatrixStack.h"
#include "Sprite.h"
#include "SpriteStage.h"

namespace bamf {

/**
	A sprite stream is used to send sprites to the
	frame buffer
 */
class SpriteStream {
public:
	
	explicit SpriteStream();
	virtual ~SpriteStream();
	
	void renderStage(SpriteStage & stage);
	
private:
	SpriteStream(const SpriteStream &);
	SpriteStream & operator=(const SpriteStream &);
};

}

#endif /* defined(__Bamf__SpriteStream__) */
