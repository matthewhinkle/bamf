//
//  Scene.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#include "Scene.h"

#include "BamfObject.h"
#include "SceneLayer.h"

namespace bamf {

const float Scene::kPhysicsLayer = 0.0f;
const float Scene::kBackgroundLayer = 0.10f;
const float Scene::kForegroundFarLayer = 0.50f;
const float Scene::kForegroundMidLayer = 0.60f;
const float Scene::kForegroundNearLayer = 0.70f;
const float Scene::kHudLayer = 0.99f;

Scene::Scene() { }

Scene::~Scene()
{
	if(this->layerByZValue.size() > 0) {
		std::map<float, SceneLayer *>::iterator i;
		for(i = this->layerByZValue.begin(); i != this->layerByZValue.end(); i++) {
			if(i->second) {
				delete i->second;
				i->second = NULL;
			}
			
			this->layerByZValue.erase(i);
		}
	}

	this->layerByObjectId.clear();
}

void Scene::addObjectWithZValue(BamfObject * bamf, float layerZValue)
{
	if(!(bamf)) return;

	std::map<float, SceneLayer *>::const_iterator i = this->layerByZValue.find(layerZValue);
	
	if(i == this->layerByZValue.end()) {
		/* layer does not exist, create it */
		SceneLayer * layer = new SceneLayer();
		layer->addObject(bamf);
		this->layerByZValue.insert(std::pair<float, SceneLayer *>(layerZValue, layer));
		this->layerByObjectId.insert(std::pair<uint64_t, SceneLayer *>(bamf->getId(), layer));
	} else {
		/* layer exists, add the object */
		i->second->addObject(bamf);
		this->layerByObjectId.insert(std::pair<uint64_t, SceneLayer *>(bamf->getId(), i->second));
	}
}

BamfObject * Scene::removeObject(uint64_t id)
{
	std::unordered_map<uint64_t, SceneLayer *>::iterator i = this->layerByObjectId.find(id);
	if(i == this->layerByObjectId.end()) {
		return NULL;
	}
	
	BamfObject * bamf = i->second->removeObject(id);
	if(i->second->getObjectCount() <= 0) {
		delete i->second;
		i->second = NULL;
		this->layerByObjectId.erase(i);
	}
	
	return bamf;
}

BamfObject * Scene::removeObject(BamfObject * bamf)
{
	return bamf ? this->removeObject(bamf->getId()) : NULL;
}

void Scene::removeLayerWithZValue(float zValue)
{
	std::map<float, SceneLayer *>::iterator i = this->layerByZValue.find(zValue);
	if(i == this->layerByZValue.end()) {
		return;
	}
	
	delete i->second;
	i->second = NULL;
	this->layerByZValue.erase(i);
}

BamfObject * Scene::getObjectById(uint64_t id) const {
	std::unordered_map<uint64_t, SceneLayer *>::const_iterator i = this->layerByObjectId.find(id);
	if(i == this->layerByObjectId.end()) {
		return NULL;
	}
	
	return i->second->getObjectById(id);
}

void Scene::update( unsigned dt)
{
	std::for_each(this->layerByZValue.begin(), this->layerByZValue.end(), [=](std::pair<float, SceneLayer *> i) { i.second->update(this, dt); });
}

void Scene::draw(SpriteStream * spriteStream, unsigned dt)
{
	std::for_each(this->layerByZValue.begin(), this->layerByZValue.end(), [=](std::pair<float, SceneLayer *> i) { i.second->draw(spriteStream, dt); });
}

}