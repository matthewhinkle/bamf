//
//  Action.h
//  Bamf
//
//  Created by Mike Hershey on 2/11/13.
//
//

#ifndef Bamf_Action_h
#define Bamf_Action_h

#include "SMSPacket.h"

namespace bamf {

class Action
{
    
public:
    virtual ~Action() {}
    
    virtual void executeAction() = 0;
    virtual SMSPacket * packetForAction() = 0;
    
};
    
}

#endif
