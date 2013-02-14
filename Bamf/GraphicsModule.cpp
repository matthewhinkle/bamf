//
//  GraphicsLoop.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/14/13.
//
//

#include "GraphicsModule.h"

namespace bamf {

GraphicsModule::GraphicsModule(int width, int height)
{
}

GraphicsModule::~GraphicsModule() { }

void GraphicsModule::init()
{
	
}

void GraphicsModule::update(unsigned delta)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	SDL_GL_SwapWindow(this->window);

#if 0
	Sprite sprite("/bamf/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	
	Sprite hair("/bamf/crosshair.png");
	hair.load(man);
	hair.setHotspot(hair.getBounds().getCenter());

	Viewport * viewport = this->camera->getViewport();
	viewport->clear();

	MatrixStack::setMatrixMode(bamf::kMatrixModeProjection);
	MatrixStack::loadMatrix(viewport->getPerspective());
	MatrixStack::setMatrixMode(bamf::kMatrixModeModel);
	
	spriteStream->begin(glm::mat4());
	for(int i = 0; i < 1; i++) {
		for(int j = 0; j < 1; j++) {
			spriteStream->draw(&sprite, glm::vec2(i * 200, j * 300));
		}
	}
	spriteStream->end();
	
	spriteStream->begin(this->getCamera()->computeTransform(), bamf::kSpriteStreamClipEdges);
	spriteStream->draw(&hair, this->getCamera()->getPosition());
	spriteStream->end();
	
	this->spriteStream->flush();
	
	MatrixStack::loadMatrix(glm::mat4());
	
	SDL_GL_SwapWindow(this->window);
#endif
}

}
