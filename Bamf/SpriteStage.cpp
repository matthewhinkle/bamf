//
//  SpriteStage.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/9/13.
//
//

#include "SpriteStage.h"

namespace bamf {

SpriteStage::SpriteStage(const glm::mat4 & transform)
	:
	base(transform)
{ }

SpriteStage::SpriteStage(const MatrixStack & matrixStack)
	:
	base(matrixStack.top())
{ }

SpriteStage::~SpriteStage() { }

SpriteStage * SpriteStage::draw(Sprite & sprite, const glm::vec2 & position)
{
	const Texture2D * texture = sprite.getTexture();
	if(!(sprite.getTexture())) {
		return this;
	}

	glm::mat4 transform = glm::translate(this->base, glm::vec3(position[0], position[1], 0.0f));
	
	this->targets.insert(std::make_pair(texture->getId(), std::pair<Sprite &, glm::mat4>(sprite, transform)));
	
	return this;
}

}
