//
//  SpriteStream.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/9/13.
//
//

#include "SpriteStream.h"

namespace bamf {

SpriteStream::SpriteStream() { }

SpriteStream::~SpriteStream() { }

void SpriteStream::renderStage(SpriteStage & stage)
{
	std::multimap<uint64_t, std::pair<Sprite &, glm::mat4> >::iterator i;
	std::multimap<uint64_t, std::pair<Sprite &, glm::mat4> >::iterator base;
	std::multimap<uint64_t, std::pair<Sprite &, glm::mat4> >::iterator end = stage.targetsEnd();
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	for(i = base = stage.targetsBegin(); i != end; i++) {
		if(base->first < i->first) {
			/* changed textures */
			base = i;
		}
		
		Sprite & sprite = i->second.first;
		/* this call to bind should be a nop if it is already bound, so no need to check */
		sprite.bind();
		
		MatrixStack::loadMatrix(i->second.second);

		glDrawArrays(GL_QUADS, 0, sprite.getVertexCount());
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	
	MatrixStack::loadMatrix(glm::mat4());
}

}