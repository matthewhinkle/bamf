//
//  NavigationMesh.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/9/13.
//
//

#ifndef __Bamf__NavigationMesh__
#define __Bamf__NavigationMesh__

#include "Graph.h"
#include "Hashes.h"
#include "Scene.h"

namespace bamf {

class NavigationMesh {
public:

	explicit NavigationMesh(Scene * scene);
	virtual ~NavigationMesh();
	
	inline const Graph<glm::vec2, float> * getGraph() const { return &this->graph; }

private:
	Graph<glm::vec2, float> graph;

	Scene * scene;

	NavigationMesh(const NavigationMesh &);
	NavigationMesh & operator=(const NavigationMesh &);
};

}

#endif /* defined(__Bamf__NavigationMesh__) */
