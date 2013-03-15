//
//  NavigationMesh.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/9/13.
//
//

#ifndef __Bamf__NavigationMesh__
#define __Bamf__NavigationMesh__

#include <climits>
#include <unordered_map>

#include "Aabb.h"
#include "BamfObject.h"
#include "Graph.h"
#include "Hashes.h"
#include "Line.h"
#include "NavigationStrategy.h"\

namespace bamf {

class Scene;

class NavigationMesh {
public:

	explicit NavigationMesh(Scene * scene);
	virtual ~NavigationMesh();
	
	void computeGraph(NavigationStrategy * navigationStrategy, CollisionObject * src, CollisionObject * dst);
	
	bool objectsCollideWithAabb(const Aabb<int> & aabb);
	
	bool hasClearPath(const Aabb<int> & src, const Aabb<int> & dest);
	
	inline const Aabb<int> & getStart() const { return this->start; }
	inline const Aabb<int> & getDestination() const { return this->destination; }
	
	inline Scene * getScene() const { return this->scene; }
	
	inline Graph<Aabb<int>, float, std::hash<Aabb<int>>> * getGraph() { return &this->graph; }

	Aabb<int> start;

private:
	Graph<Aabb<int>, float, std::hash<Aabb<int>>> graph;
	Scene * scene;
	
	CollisionObject * src;
	CollisionObject * dst;
	
	void getAabbs(const Aabb<int> & a, std::vector<Aabb<int>> & aabbs);
	void navigate(NavigationStrategy * navigationStrategy, CollisionObject * collisionObject);
	
	Aabb<int> destination;

	NavigationMesh(const NavigationMesh &);
	NavigationMesh & operator=(const NavigationMesh &);
};

}

#endif /* defined(__Bamf__NavigationMesh__) */
