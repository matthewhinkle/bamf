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

std::vector<IKeyMapping *> * InputMapping::getKeyMappings()
{
    return this->keyMappings;
}

void InputMapping::dispatchKeyEvent(KeyPressType pressType, int keyCode, ...)
{
    for(int i = 0; i < this->keyMappings->size(); i++) {
        IKeyMapping * keyMapping = (*this->keyMappings)[i];
        if(keyMapping->appliesForInput(pressType, keyCode /*TODO key masks*/)) {
            Action * action = keyMapping->actionForInput();
            action->executeAction();
            delete action;
        }
    }
}