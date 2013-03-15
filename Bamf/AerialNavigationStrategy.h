//
//  AerialNavigationStrategy.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/13/13.
//
//

#ifndef __Bamf__AerialNavigationStrategy__
#define __Bamf__AerialNavigationStrategy__

#include "NavigationStrategy.h"
#include "Scene.h"

namespace bamf {

class AerialNavigationStrategy : public NavigationStrategy {
public:

	AerialNavigationStrategy(Scene * scene);
	virtual ~AerialNavigationStrategy();
	
	virtual void discoverPotentialNeighbors(CollisionObject * collisionObject, BamfObject * bamf, std::unordered_set<CollisionObject *> & neighbors) const;
	
private:
	Scene * scene;
	
	AerialNavigationStrategy(const AerialNavigationStrategy &);
	AerialNavigationStrategy & operator=(const AerialNavigationStrategy &);
};

}

#endif /* defined(__Bamf__AerialNavigationStrategy__) */
