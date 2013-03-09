//
//  Scene.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#ifndef Bamf_Scene_h
#define Bamf_Scene_h

#include <unordered_map>

#include "BamfObject.h"
#include "CollisionObject.h"
#include "CollisionLayer.h"
#include "Event.h"
#include "EventPublisher.h"
#include "Drawable.h"
#include "MatrixStack.h"
#include "Rectangle.h"
#include "SpriteStream.h"
#include "SceneLayer.h"
#include "ViewLayer.h"

namespace bamf {

class Scene : public Drawable {
public:

	Scene();
	virtual ~Scene();
	
	inline const Rectangle & getBounds() const { return this->bounds; }
	
	void addObjectWithZValue(BamfObject * bamf, unsigned layerZValue, bool collidable = true);
		
	BamfObject * removeObject(uint64_t id);
	BamfObject * removeObject(BamfObject * bamf);
	
	void removeLayerWithZValue(unsigned zValue);
	BamfObject * getObjectById(uint64_t id) const;
	
	void update(unsigned dt);
	void draw(SpriteStream * spriteStream, unsigned dt);
	
	inline CollisionLayer * getCollisionLayer() { return &this->collisionLayer; }
	
	inline uint64_t onBoundsResize(const std::function<void (Event<Scene *, Rectangle> *)> & doFunc) { return this->onBoundsResizePublisher.subscribe(doFunc); }
	inline void onBoundsResizeUnsubscribe(uint64_t subscriberId) { this->onBoundsResizePublisher.unsubscribe(subscriberId); }
	
	/* common layers */
	static const unsigned kBackgroundLayer;
	static const unsigned kForegroundFarLayer;
	static const unsigned kForegroundMidLayer;
	static const unsigned kForegroundNearLayer;
	static const unsigned kHudLayer;
	
private:
	void resizeBoundsIfNeeded(BamfObject * bamf);
	ViewLayer * getLayerWithZValue(unsigned layerZValue);

	std::unordered_map<uint64_t, ViewLayer *> layerByObjectId;
	std::map<unsigned, ViewLayer *> layerByZValue;
	
	EventPublisher<Scene *, Rectangle> onBoundsResizePublisher;
	
	CollisionLayer collisionLayer;
	Rectangle bounds;
	
	Scene(const Scene &);
	Scene & operator=(const Scene &);
};

}

#endif
