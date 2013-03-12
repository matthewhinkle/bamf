//
//  NavigationMesh.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/9/13.
//
//

#include "NavigationMesh.h"

namespace bamf {

NavigationMesh::NavigationMesh(Scene * scene)
	:
	scene(scene),
	graph()
{ }

NavigationMesh::~NavigationMesh() { }

void NavigationMesh::doit()
{
	CollisionLayer * collisionLayer = this->scene->getCollisionLayer();
	
	collisionLayer->foreachObject(16, [=](CollisionObject * obj, unsigned dt) {
		
	});
}

}
