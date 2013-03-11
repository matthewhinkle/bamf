    //
//  InputMapping.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#include "InputMapping.h"

namespace bamf {

InputMapping::InputMapping()
: keyMappings(new std::vector<IKeyMapping *>())
, quitHandler(new DefaultQuitHandler())
{
    
}

void InputMapping::addKeyMapping(IKeyMapping * keyMapping) {
    this->keyMappings->push_back(keyMapping);
}

std::vector<IKeyMapping *> * InputMapping::getKeyMappings()
{
    return this->keyMappings;
}

void InputMapping::dispatchKeyEvent(NetworkingModule * networkingModule, KeyPressType pressType, int keyCode, ...)
{
    for(int i = 0; i < this->keyMappings->size(); i++) {
        IKeyMapping * keyMapping = (*this->keyMappings)[i];
        if(keyMapping->appliesForInput(pressType, keyCode /*TODO key masks*/)) {
            Action * action = keyMapping->actionForInput();
            action->executeAction();
            if(networkingModule != NULL) {
               networkingModule->sendPacket(action->packetForAction());
            }
            delete action;
        }
    }
}

void InputMapping::setQuitHandler(IQuitHandler * quitHandler)
{
    this->quitHandler = quitHandler;
}

IQuitHandler * InputMapping::getQuitHandler()
{
    return quitHandler;
}

}