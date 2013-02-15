//
//  Bamf.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef Bamf_Bamf_h
#define Bamf_Bamf_h

#include <cstdint>

#include "glm/glm.hpp"

#include "Drawable.h"
#include "Updateable.h"

namespace bamf {

/**
	First class game object interface
 */
class BamfObject : public Drawable, public Updateable {
private:
    uint64_t objectId;
public:

	explicit BamfObject();
	
	virtual glm::vec2 getPosition() const;
    
    uint64_t getObjectID();
    void setObjectID(uint64_t objectID);
	
	void update(unsigned delta);
	void draw(SpriteStream * spriteStream, unsigned delta);
	
private:
	BamfObject(const BamfObject &);
	BamfObject & operator=(const BamfObject &);
};

}

#endif
