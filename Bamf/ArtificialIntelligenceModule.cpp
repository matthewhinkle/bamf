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
}

}
