//
//  Scene.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#include "Scene.h"

namespace bamf {

const unsigned Scene::kBackgroundLayer = 100;
const unsigned Scene::kForegroundFarLayer = 500;
const unsigned Scene::kForegroundMidLayer = 600;
const unsigned Scene::kForegroundNearLayer = 700;
const unsigned Scene::kHudLayer = 999;

Scene::Scene()
	:
	collisionLayer(this),
	onObjectMovePublisher(this),
	onBoundsResizePublisher(this)
{ }

Scene::~Scene()
{
	if(this->layerByZValue.size() > 0) {
		std::map<unsigned, ViewLayer *>::iterator i;
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

void Scene::addObjectWithZValue(BamfObject * bamf, unsigned layerZValue, bool collidable)
{
	if(bamf && !(this->getObjectById(bamf->getId()))) {
		ViewLayer * viewLayer = this->getLayerWithZValue(layerZValue);
		viewLayer->addObject(bamf);
		this->layerByObjectId.insert(std::pair<uint64_t, ViewLayer *>(bamf->getId(), viewLayer));

		if(collidable) {
			this->collisionLayer.addObject(bamf);
		}
		
		bamf->onMove([=](Event<BamfObject *, glm::vec2> * e) {
			this->resizeBoundsIfNeeded(e->getSender());
			this->onObjectMovePublisher.publish(e->getSender());
		});
		
		this->resizeBoundsIfNeeded(bamf);
	}
}

BamfObject * Scene::removeObject(uint64_t id)
{
	std::unordered_map<uint64_t, ViewLayer *>::iterator i = this->layerByObjectId.find(id);
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

void Scene::removeLayerWithZValue(unsigned zValue)
{
	std::map<unsigned, ViewLayer *>::iterator i = this->layerByZValue.find(zValue);
	if(i == this->layerByZValue.end()) {
		return;
	}
	
	delete i->second;
	i->second = NULL;
	this->layerByZValue.erase(i);
}

BamfObject * Scene::getObjectById(uint64_t id) const {
	std::unordered_map<uint64_t, ViewLayer *>::const_iterator i = this->layerByObjectId.find(id);
	if(i == this->layerByObjectId.end()) {
		return NULL;
	}
	
	return i->second->getObjectById(id);
}

void Scene::update(unsigned dt)
{
	std::for_each(this->layerByZValue.begin(), this->layerByZValue.end(), [=](std::pair<float, ViewLayer *> i) { i.second->update(this, dt); });
}

void Scene::draw(SpriteStream * spriteStream, unsigned dt)
{
	std::for_each(this->layerByZValue.begin(), this->layerByZValue.end(), [=](std::pair<float, ViewLayer *> i) { i.second->draw(spriteStream, dt); });
}

void Scene::resizeBoundsIfNeeded(bamf::BamfObject * bamf)
{
	const glm::vec2 normPos = bamf->getPosition() - bamf->getHotspot();
	const Rectangle bounds = bamf->getBounds();
	
	bool resized = false;
	if(normPos.x < this->bounds.x) {
		this->bounds.x = normPos.x;
		resized = true;
	}
	
	if(normPos.y < this->bounds.y) {
		this->bounds.y = normPos.y;
		resized = true;
	}
	
	const int right = static_cast<int>(normPos.x) + bounds.width;
	if(right > this->bounds.getRight()) {
		this->bounds.width = right - this->bounds.x;
		resized = true;
	}
	
	const int top = static_cast<int>(normPos.y) + bounds.height;
	if(top > this->bounds.getTop()) {
		this->bounds.height = top - this->bounds.y;
		resized = true;
	}
	
	if(resized) {
		this->onBoundsResizePublisher.publish(this->bounds);
	}
}

ViewLayer * Scene::getLayerWithZValue(unsigned layerZValue)
{
	std::map<unsigned, ViewLayer *>::const_iterator i = this->layerByZValue.find(layerZValue);
	
	ViewLayer * layer = NULL;
	if(i == this->layerByZValue.end()) {
		/* layer does not exist, create it */
		layer = new ViewLayer();
		this->layerByZValue.insert(std::pair<float, ViewLayer *>(layerZValue, layer));
	} else {
		layer = i->second;
	}
	
	SDL_assert(layer);
	
	return layer;
}

}