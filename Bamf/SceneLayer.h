//
//  SceneLayer.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#ifndef __Bamf__SceneLayer__
#define __Bamf__SceneLayer__

#include <unordered_map>

#include "BamfObject.h"
#include "SpriteStream.h"

#include "Scene.h"
#include "Updateable.h"
#include "Drawable.h"

namespace bamf {

/**
	A single layer in a Scene.  Objects drawn on the
	same layer have no defined order
 */
class SceneLayer : public Updateable, public Drawable {
public:

	explicit SceneLayer();
	virtual ~SceneLayer();
	
	void addObject(BamfObject * bamf);
	
	BamfObject * removeObject(uint64_t id);
	BamfObject * removeObject(BamfObject * bamf);
	
	inline unsigned getObjectCount() const { return static_cast<unsigned>(this->objectById.size()); }
	
	inline BamfObject * getObjectById(uint64_t id) const {
		std::unordered_map<uint64_t, BamfObject *>::const_iterator i = this->objectById.find(id);
		
		return i == this->objectById.end() ? NULL : i->second;
	}
	
	void update(Scene * scene, unsigned dt);
	
	void draw(SpriteStream * spriteStream, unsigned delta);
	
private:
	std::unordered_map<uint64_t, BamfObject *> objectById;

	SceneLayer(const SceneLayer &);
	SceneLayer & operator=(const SceneLayer &);
};

}

#endif /* defined(__Bamf__SceneLayer__) */
