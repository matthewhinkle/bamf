//
//  CollisionLayer.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/8/13.
//
//

#ifndef __Bamf__CollisionLayer__
#define __Bamf__CollisionLayer__

#include <map>

#include "SDL2/SDL.h"

#include "CollisionObject.h"
#include "Event.h"
#include "Hashes.h"
#include "SceneLayer.h"
#include "SpriteStream.h"
#include "QuadTree.h"

#include "RealTimeAstar.h"

namespace bamf {

class Scene;

class CollisionLayer : public SceneLayer<uint64_t, CollisionObject *> {
public:

	CollisionLayer(Scene * scene);
	virtual ~CollisionLayer();
	
	virtual void addObject(BamfObject * bamf);
	
	virtual CollisionObject * getObjectById(uint64_t id);
	virtual inline unsigned getObjectCount() const { return static_cast<unsigned>(this->objectById.size()); }
	
	virtual CollisionObject * removeObject(uint64_t id);
	virtual CollisionObject * removeObject(BamfObject * bamf);
	
	virtual void update(Scene * scene, unsigned dt) { if(this->realTimeAstar) { this->realTimeAstar->update(scene, dt); } }
	virtual void draw(SpriteStream * spriteStream, unsigned dt) { }
	
	virtual void foreachObject(const std::function<void (CollisionObject *)> & doFunc);
	virtual void foreachObject(unsigned dt, const std::function<void (CollisionObject *, unsigned)> & doFunc);
	virtual void foreachPair(unsigned dt, const std::function<void (CollisionObject *, CollisionObject *, unsigned)> & doFunc);
	
	unsigned findObjectsIntersectingLine(const Line<int> & line, std::unordered_set<CollisionObject *> & objects);
	unsigned findObjectsIntersectingAabb(const Aabb<int> & aabb, std::unordered_set<CollisionObject *> & objects);
	
private:
	Scene * scene;
	std::unordered_map<uint64_t, CollisionObject *> objectById;
	
	RealTimeAstar * realTimeAstar;
	
	uint64_t onObjectMoveId;
	uint64_t onBoundsResizeId;
	
	Aabb<int> aabb;
	QuadTree<CollisionObject *, int> qTree;

	CollisionLayer(const CollisionLayer &);
	CollisionLayer & operator=(const CollisionLayer &);
};

}

#endif /* defined(__Bamf__CollisionLayer__) */
