//
//  ViewLayer.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#include "ViewLayer.h"

#include "Scene.h"

namespace bamf {

ViewLayer::ViewLayer()
	:
	objectById()
{ }

ViewLayer::~ViewLayer()
{
	this->objectById.clear();
}

void ViewLayer::addObject(bamf::BamfObject * bamf)
{
	if(!(bamf)) {
		return;
	}
	
	this->objectById[bamf->getId()] = bamf;
}

BamfObject * ViewLayer::removeObject(uint64_t id)
{
	std::unordered_map<uint64_t, BamfObject *>::iterator i = this->objectById.find(id);
	if(i != this->objectById.end()) {
		BamfObject * bamf = i->second;
		this->objectById.erase(i);
		
		return bamf;
	}
	
	return NULL;
}

BamfObject * ViewLayer::removeObject(BamfObject * bamf)
{
	return bamf ? this->removeObject(bamf->getId()) : NULL;
}

void ViewLayer::update(Scene * scene, unsigned dt)
{
	std::for_each(this->objectById.begin(), this->objectById.end(), [=](std::pair<uint64_t, BamfObject *> i) { i.second->update(scene, dt); });
}

void ViewLayer::draw(bamf::SpriteStream * spriteStream, unsigned dt)
{
	std::for_each(this->objectById.begin(), this->objectById.end(), [=](std::pair<uint64_t, BamfObject *> i) { i.second->draw(spriteStream, dt); });
}

}