//
//  BamfObject.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/8/13.
//
//

#ifndef Bamf_Bamf_h
#define Bamf_Bamf_h

#include "glm/glm.hpp"

#include "EventPublisher.h"
#include "Drawable.h"
#include "Updateable.h"

namespace bamf {

class Scene;

/**
	First class game object
 */
class BamfObject : public Updateable, public Drawable {
public:

	explicit BamfObject(bool owned = false);
    explicit BamfObject(u_int64_t id, bool owned = false);
	virtual ~BamfObject();
    
	inline uint64_t getId() const { return this->id; }
	
	inline virtual const glm::vec2 & getPosition() const { return this->position; }
	virtual const glm::vec2 & getHotspot() const = 0;
	virtual const Rectangle & getBounds() const = 0;
	
	inline virtual void setPosition(const glm::vec2 & position, bool publish = true) {
		this->position = position;
		
		if(publish) {
			this->onMovePublisher.publish(position);
		}
	}
	
	virtual void update(Scene * scene, unsigned dt) { }
	virtual void draw(SpriteStream * spriteStream, unsigned dt) { }
	
	inline uint64_t onMove(const std::function<void (Event<BamfObject *, glm::vec2> *)> & doFunc) { return this->onMovePublisher.subscribe(doFunc); }
	inline void onMoveUnsubscribe(uint64_t subscriberId) { this->onMovePublisher.unsubscribe(subscriberId); }
	
protected:
	uint64_t id;
	bool owned;
	glm::vec2 position;

private:
	EventPublisher<BamfObject *, glm::vec2> onMovePublisher;

	static uint64_t idCounter;
	static uint64_t nextId();
	
	static const Rectangle defaultBounds;
	static const glm::vec2 defaultHotspot;
	
	BamfObject(const BamfObject &);
	BamfObject & operator=(const BamfObject &);
};

}

#endif
