//
//  AerialNavigationStrategy.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/13/13.
//
//

#include "AerialNavigationStrategy.h"

namespace bamf {

static inline Aabb<int> makeDiscoveryAabb(int distanceLevel);
static inline Aabb<int> centeredAabb(const glm::vec2 & center, const Rectangle & bounds);
static inline Aabb<int> rightAabb(const glm::vec2 & right, const Rectangle & bounds);

enum {
	kXMinBase = -512,
	kYMinBase = -384,
	kXMaxBase = -kXMinBase,
	kYMaxBase = -kYMinBase
};

enum {
	kMaxDistanceLevel = 20
};

AerialNavigationStrategy::AerialNavigationStrategy(Scene * scene)
	:
	scene(scene)
{ }

AerialNavigationStrategy::~AerialNavigationStrategy() { }

void AerialNavigationStrategy::discoverPotentialNeighbors(
	CollisionObject * collisionObject,
	BamfObject * bamf,
	std::unordered_set<CollisionObject *> & potentialNeigbors) const
{
	std::unordered_set<CollisionObject *> s;
	for(int i = 0; s.empty() && i < kMaxDistanceLevel; i++) {
		Aabb<int> discoveryAabb = makeDiscoveryAabb(i);
		this->scene->getCollisionLayer()->findObjectsIntersectingAabb(discoveryAabb, s);
	}
	
	s.erase(this->scene->getCollisionLayer()->getObjectById(bamf->getId()));
	s.erase(collisionObject);
	
	potentialNeigbors.insert(s.begin(), s.end());
}

static inline Aabb<int> makeDiscoveryAabb(int distanceLevel) {
	int multiplier = 1;
	for(int i = 0; i < distanceLevel; multiplier <<= 1)
		;
	
	return Aabb<int>(
		kXMinBase * multiplier,
		kYMinBase * multiplier,
		kXMaxBase * multiplier,
		kYMaxBase * multiplier);
}

static inline Aabb<int> centeredAabb(const glm::vec2 & center, const Rectangle & bounds)
{
	return Aabb<int>(
		center.x - (bounds.width >> 1),
		center.y - (bounds.height >> 1),
		center.x + (bounds.width >> 1),
		center.y + (bounds.height >> 1)
	);
}

}