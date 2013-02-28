//
//  SceneManager.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#include "SceneManager.h"

namespace bamf {

SceneManager::SceneManager()
	:
	scenes()
{ }

SceneManager::~SceneManager() { }

void SceneManager::pushScene(Scene * scene)
{
	if(!(scene)) return;
	
	this->scenes.push(scene);
}

Scene * SceneManager::popScene(unsigned num)
{
	if(this->scenes.empty()) {
		return NULL;
	}
	
	if(!(num = glm::min(num, static_cast<unsigned>(this->scenes.size())))) {
		return NULL;
	}
	
	Scene * popped = NULL;
	for(unsigned i = 0; i < num; i++) {
		if(i == num - 1) {
			popped = this->scenes.top();
		}
		
		this->scenes.pop();
	}
	
	return popped;
}

void SceneManager::update(Scene * scene, unsigned dt)
{
	Scene * currentScene = this->getCurrentScene();
	if(!(currentScene)) {
		return;
	}
	
	currentScene->update(dt);
}

void SceneManager::draw(SpriteStream * spriteStream, unsigned dt)
{
	Scene * currentScene = this->getCurrentScene();
	if(!(currentScene)) {
		return;
	}
	
	currentScene->draw(spriteStream, dt);
}

}
