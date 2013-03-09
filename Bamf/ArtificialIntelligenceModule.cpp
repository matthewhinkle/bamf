//
//  ArtificialIntelligenceModule.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 3/7/13.
//
//

#include "ArtificialIntelligenceModule.h"

#include <iostream>

namespace bamf {

ArticialIntelligenceModule::ArticialIntelligenceModule()
	:
	agentById()
{ }

ArticialIntelligenceModule::~ArticialIntelligenceModule()
{
	this->agentById.clear();
}

void ArticialIntelligenceModule::init() { }

void ArticialIntelligenceModule::update(Scene * scene, unsigned dt)
{
#if 0
/*
	std::unordered_map<uint64_t, BamfObject *>::iterator i;
	for(i = this->agentById.begin(); i != this->agentById.end(); i++) {
		BamfObject * bamf = i->second;
		ObjectState * state = bamf->getState();
		
		ActivePath<glm::vec2> * activePath = state->activePath;
		if(activePath) {
			CollisionRectangle * collisionShape = state->collisionShape;
			RigidBody * rigidBody = collisionShape->getRigidBody();
		
			glm::vec2 localGoal = activePath->getLocalGoal();
			if(MathCommons::vectorsAreEqual(bamf->getPosition(), localGoal, 1)) {
				state->activePath->advanceNode();
				localGoal = activePath->getLocalGoal();
			} else {
				std::cout << bamf->getPosition().x << "," << bamf->getPosition().y << "\t" << localGoal.x << "," << localGoal.y << std::endl;
			}
			
			if(MathCommons::vectorsAreEqual(bamf->getPosition(), activePath->getGlobalGoal())) {
				delete state->activePath;
				state->activePath = NULL;
				state->destination = bamf->getPosition();
				rigidBody->setLinearVeloctiy(glm::vec2(0, 0));
			} else {
				glm::vec2 diff = glm::normalize((activePath->getLocalGoal() - rigidBody->getPosition()));
				rigidBody->setLinearVeloctiy(diff);
			}
		} else if(bamf->getPosition() != state->destination) {
			
		}
	}
*/
#endif
}

}
