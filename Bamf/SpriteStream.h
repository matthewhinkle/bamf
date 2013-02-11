//
//  SpriteStream.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/9/13.
//
//

#ifndef __Bamf__SpriteStream__
#define __Bamf__SpriteStream__

#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "MatrixStack.h"
#include "Sprite.h"

namespace bamf {

/**
	A sprite stream is used to send sprites to the
	frame buffer
 */
class SpriteStream {
public:
	
	explicit SpriteStream();
	virtual ~SpriteStream();
	
	SpriteStream & begin(const glm::mat4 & transform = glm::mat4());
	SpriteStream & draw(const Sprite * sprite, const glm::vec2 & position = glm::vec2());
	SpriteStream & end();
	
private:
	void flush();

	GLuint vbo;
		
	glm::mat4 transform;
	std::multimap<const Sprite *, glm::vec3> sprites;

	SpriteStream(const SpriteStream &);
	SpriteStream & operator=(const SpriteStream &);
};

}

#endif /* defined(__Bamf__SpriteStream__) */
