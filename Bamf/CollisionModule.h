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

namespace bamf {

class CollisionModule : public Module {
public:

	explicit CollisionModule() { }
	virtual ~CollisionModule() { }
	
	void init() { }
	
	void update(unsigned dt) { }

};

}

#endif /* defined(__Bamf__CollisionModule__) */
