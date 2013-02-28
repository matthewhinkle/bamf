//
//  CollisionModule.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/23/13.
//
//

#ifndef __Bamf__CollisionModule__
#define __Bamf__CollisionModule__

#include "Module.h"
#include "CollisionEvent.h"
#include "CollisionShape.h"
#include <vector>

namespace bamf {

class CollisionModule : public Module {
public:

	explicit CollisionModule() { }
	virtual ~CollisionModule() { }
	
	void init() { }
	
	void update(Scene * scene, unsigned dt) { }
    std::vector<CollisionEvent> checkCollisions();
    void addCollidable(CollisionShape s);
private:
    std::vector<CollisionShape> collidables;

};

}

#endif /* defined(__Bamf__CollisionModule__) */
