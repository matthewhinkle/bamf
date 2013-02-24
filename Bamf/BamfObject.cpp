//
//  BamfObject.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/14/13.
//
//

#include "BamfObject.h"

namespace bamf {

uint64_t BamfObject::idCounter = 0;

BamfObject::BamfObject()
	:
	id(nextId())
{ }

BamfObject::~BamfObject() { }

uint64_t BamfObject::nextId()
{
	return __sync_fetch_and_add(&BamfObject::idCounter, 1);
}

}