//
//  BamfObject.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/14/13.
//
//

#include "BamfObject.h"

#include "Scene.h"

namespace bamf {

uint64_t BamfObject::idCounter = 0;

BamfObject::BamfObject(bool owned)
	:
	id(nextId()),
	owned(owned),
	state(new ObjectState())
{ }

BamfObject::BamfObject(ObjectState * state, bool owned)
	:
	id(nextId()),
	state(state),
	owned(owned)
{ }

BamfObject::~BamfObject() { }

uint64_t BamfObject::nextId()
{
	return __sync_fetch_and_add(&BamfObject::idCounter, 1);
}

}