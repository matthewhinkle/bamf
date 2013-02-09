//
//  SpriteStage.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/9/13.
//
//

#ifndef __Bamf__SpriteStage__
#define __Bamf__SpriteStage__

#include <map>

#include "glm/glm.hpp"

#include "MatrixStack.h"
#include "Sprite.h"

namespace bamf {

class SpriteStage {
public:

	explicit SpriteStage(const glm::mat4 & transform = glm::mat4());
	explicit SpriteStage(const MatrixStack & matrixStack);
	virtual ~SpriteStage();

	SpriteStage * draw(Sprite & sprite, const glm::vec2 & position = glm::vec2(0.0f, 0.0f));

	SpriteStage * end();

	inline std::multimap<uint64_t, std::pair<Sprite &, glm::mat4> >::iterator targetsBegin() { return this->targets.begin(); }
	inline std::multimap<uint64_t, std::pair<Sprite &, glm::mat4> >::iterator targetsEnd() { return this->targets.end(); }

private:
	std::multimap<uint64_t, std::pair<Sprite &, glm::mat4>> targets;
	glm::mat4 base;

	SpriteStage(const SpriteStage &);
	SpriteStage & operator=(const SpriteStage &);
};

}

#endif /* defined(__Bamf__SpriteStage__) */
