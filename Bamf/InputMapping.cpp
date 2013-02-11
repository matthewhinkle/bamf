//
//  InputMapping.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#include "InputMapping.h"

InputMapping::InputMapping()
: keyMappings(new std::vector<IKeyMapping *>())
{
    
}

void InputMapping::addKeyMapping(IKeyMapping * keyMapping) {
    this->keyMappings->push_back(keyMapping);
}