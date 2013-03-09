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
#include "SceneLayer.h"
#include "SpriteStream.h"

namespace bamf {

class Scene;

class CollisionLayer : public SceneLayer<uint64_t, CollisionObject *> {
public:

	CollisionLayer();
	virtual ~CollisionLayer();
	
	virtual void addObject(CollisionObject * collisionObject);
	
	virtual CollisionObject * getObjectById(uint64_t id) const;
	virtual inline unsigned getObjectCount() const { return static_cast<unsigned>(this->objectById.size()); }
	
	virtual CollisionObject * removeObject(uint64_t id);
	virtual CollisionObject * removeObject(CollisionObject * collisionObject);
	
	virtual void update(Scene * scene, unsigned dt) { }
	virtual void draw(SpriteStream * spriteStream, unsigned dt) { }
	
	virtual void foreachObject(unsigned dt, const std::function<void (CollisionObject *, unsigned)> & doFunc);
	virtual void foreachPair(unsigned dt, const std::function<void (CollisionObject *, CollisionObject *, unsigned)> & doFunc);

private:
	std::map<uint64_t, CollisionObject *> objectById;

	CollisionLayer(const CollisionLayer &);
	CollisionLayer & operator=(const CollisionLayer &);
};

}

#endif /* defined(__Bamf__CollisionLayer__) */
