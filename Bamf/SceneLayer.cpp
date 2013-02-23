//
//  SceneLayer.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#include "SceneLayer.h"

namespace bamf {

SceneLayer::SceneLayer()
	:
	objectById()
{ }

SceneLayer::~SceneLayer()
{
	this->objectById.clear();
}

void SceneLayer::addObject(bamf::BamfObject * bamf)
{
	if(!(bamf)) {
		return;
	}
	
	this->objectById[bamf->getId()] = bamf;
}

BamfObject * SceneLayer::removeObject(uint64_t id)
{
	std::unordered_map<uint64_t, BamfObject *>::iterator i = this->objectById.find(id);
	if(i != this->objectById.end()) {
		BamfObject * bamf = i->second;
		this->objectById.erase(i);
		
		return bamf;
	}
	
	return NULL;
}

BamfObject * SceneLayer::removeObject(BamfObject * bamf)
{
	return bamf ? this->removeObject(bamf->getId()) : NULL;
}

void SceneLayer::update(unsigned dt)
{
	std::for_each(this->objectById.begin(), this->objectById.end(), [=](std::pair<uint64_t, BamfObject *> i) { i.second->update(dt); });
}

void SceneLayer::draw(bamf::SpriteStream * spriteStream, unsigned dt)
{
	std::for_each(this->objectById.begin(), this->objectById.end(), [=](std::pair<uint64_t, BamfObject *> i) { i.second->draw(spriteStream, dt); });
}

}