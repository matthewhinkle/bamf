//
//  NavigationStrategy.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/13/13.
//
//

#ifndef Bamf_NavigationStrategy_h
#define Bamf_NavigationStrategy_h

#include <unordered_set>
#include <vector>

#include "Aabb.h"
#include "CollisionObject.h"
#include "Graph.h"

namespace bamf {

class NavigationStrategy {
public:

	NavigationStrategy() { }
	virtual ~NavigationStrategy() { }

	virtual void discoverPotentialNeighbors(CollisionObject * collisionObject, BamfObject * bamf, std::unordered_set<CollisionObject *> & neighbors) const = 0;

private:
	NavigationStrategy(const NavigationStrategy &);
	NavigationStrategy & operator=(const NavigationStrategy &);
};

}

#endif
