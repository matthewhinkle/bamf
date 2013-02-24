//
//  BamfObject.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef Bamf_Bamf_h
#define Bamf_Bamf_h

#include <atomic>
#include <cstdint>

#include "glm/glm.hpp"

#include "Drawable.h"
#include "Updateable.h"

namespace bamf {

/**
	First class game object
 */
class BamfObject : public Drawable, public Updateable {
public:

	explicit BamfObject();
	virtual ~BamfObject();
    
	inline uint64_t getId() const { return this->id; }
	
	virtual const glm::vec2 & getPosition() const = 0;
	virtual float getZRotation() const = 0;
		
	virtual void update(unsigned dt) = 0;
	virtual void draw(SpriteStream * spriteStream, unsigned dt) = 0;
	
	inline bool operator<(const BamfObject & bamf) { return this->id < bamf.id; }
	
private:
	uint64_t id;

	BamfObject(const BamfObject &);
	BamfObject & operator=(const BamfObject &);
	
	static uint64_t idCounter;
	static inline uint64_t nextId();
};

}

#endif
