//
//  RealTimeAstar.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/13/13.
//
//

#ifndef __Bamf__RealTimeAstar__
#define __Bamf__RealTimeAstar__

#include "Astar.h"
#include "BamfObject.h"
#include "Graph.h"
#include "NavigationMesh.h"

namespace bamf {

class Scene;

class RealTimeAstar {
public:

	RealTimeAstar(Scene * scene, BamfObject * bamf);
	virtual ~RealTimeAstar();
	
	void pathTo(NavigationStrategy * navigationStrategy, BamfObject * target);
	
	virtual void update(Scene * scene, unsigned dt);

private:
	Scene * scene;

	bool pathing;
	
	int64_t timeUntilUpdate;
	
	CollisionObject * bamf;
	CollisionObject * target;
	
	NavigationMesh navigationMesh;
	
	NavigationStrategy * navigationStrategy;

	RealTimeAstar(const RealTimeAstar &);
	RealTimeAstar & operator=(const RealTimeAstar &);
};

}

#endif /* defined(__Bamf__RealTimeAstar__) */
