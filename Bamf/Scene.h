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
#include "SpriteStream.h"

#include "Drawable.h"
#include "Updateable.h"

namespace bamf {

class Scene {
public:

	Scene();
	virtual ~Scene();
	
	void addObject(BamfObject * bamf);
	
	BamfObject * removeObject(uint64_t id);
	BamfObject * removeObject(BamfObject * bamf);
	
	inline BamfObject * getObjectById(uint64_t id) const {
		std::unordered_map<uint64_t, BamfObject *>::const_iterator i = this->objectById.find(id);
		
		return i == this->objectById.end() ? NULL : i->second;
	}
	
	void update(unsigned delta);
	
	void draw(SpriteStream * spriteStream, unsigned delta);
	
private:
	std::unordered_map<uint64_t, BamfObject *> objectById;
	
	Scene(const Scene &);
	Scene & operator=(const Scene &);
};

}

#endif
