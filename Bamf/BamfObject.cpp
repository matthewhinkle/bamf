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
    owned(owned),
	onMovePublisher(this)
{
    if(owned) {
        u_int64_t r30 = RAND_MAX*rand()+rand();
        u_int64_t s30 = RAND_MAX*rand()+rand();
        u_int64_t t4  = rand() & 0xf;
        
        u_int64_t res = (r30 << 34) + (s30 << 4) + t4;
        std::cout << "Created owned object with id: " << res << "\n";
        this->id = res;
    } else {
        this->id = nextId();
    }
}
    
BamfObject::BamfObject(u_int64_t id, bool owned)
:
owned(owned),
onMovePublisher(this),
id(id)
{
}

BamfObject::~BamfObject() { }

uint64_t BamfObject::nextId()
{
	return __sync_fetch_and_add(&BamfObject::idCounter, 1);
}

}