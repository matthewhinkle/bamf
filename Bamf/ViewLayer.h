//
//  ViewLayer.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/22/13.
//
//

#ifndef __Bamf__ViewLayer__
#define __Bamf__ViewLayer__

#include <unordered_map>

#include "BamfObject.h"
#include "Drawable.h"
#include "SceneLayer.h"
#include "SpriteStream.h"
#include "Updateable.h"

namespace bamf {

class Scene;

class ViewLayer : public SceneLayer<uint64_t, BamfObject *> {
public:

	explicit ViewLayer();
	virtual ~ViewLayer();
	
	virtual void addObject(BamfObject * bamf);
	
	virtual BamfObject * removeObject(uint64_t id);
	virtual BamfObject * removeObject(BamfObject * bamf);
	
	inline unsigned getObjectCount() const { return static_cast<unsigned>(this->objectById.size()); }
	
	inline BamfObject * getObjectById(uint64_t id) const {
		std::unordered_map<uint64_t, BamfObject *>::const_iterator i = this->objectById.find(id);
		
		return i == this->objectById.end() ? NULL : i->second;
	}
	
	void update(Scene * scene, unsigned dt);
	
	void draw(SpriteStream * spriteStream, unsigned delta);

private:
	std::unordered_map<uint64_t, BamfObject *> objectById;

	ViewLayer(const ViewLayer &);
	ViewLayer & operator=(const ViewLayer &);
};

}

#endif /* defined(__Bamf__ViewLayer__) */
