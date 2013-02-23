//
//  Scene.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#include "Scene.h"

namespace bamf {

Scene::Scene() { }

Scene::~Scene()
{
	this->objectById.clear();
}

void Scene::addObject(bamf::BamfObject * bamf)
{
	if(!(bamf)) {
		return;
	}
	
	this->objectById[bamf->getId()] = bamf;
}

BamfObject * Scene::removeObject(uint64_t id)
{
	std::unordered_map<uint64_t, BamfObject *>::iterator i = this->objectById.find(id);
	if(i != this->objectById.end()) {
		BamfObject * bamf = i->second;
		this->objectById.erase(i);
		
		return bamf;
	}
	
	return NULL;
}

BamfObject * Scene::removeObject(BamfObject * bamf)
{
	return bamf ? this->removeObject(bamf->getId()) : NULL;
}

void Scene::update(unsigned dt)
{
	std::for_each(this->objectById.begin(), this->objectById.end(), [=](std::pair<uint64_t, BamfObject *> i) { i.second->update(dt); });
}

void Scene::draw(bamf::SpriteStream * spriteStream, unsigned dt)
{
	std::for_each(this->objectById.begin(), this->objectById.end(), [=](std::pair<uint64_t, BamfObject *> i) { i.second->draw(spriteStream, dt); });
}

}