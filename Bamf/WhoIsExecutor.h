//
//  WhoIsExecutor.h
//  Bamf
//
//  Created by Mike Hershey on 3/13/13.
//
//

#ifndef __Bamf__WhoIsExecutor__
#define __Bamf__WhoIsExecutor__

#include <iostream>
#include "SMSPacketExecutor.h"
#include "BamfObject.h"
#include <stdio.h>
#include <string.h>
#include "SpriteObject.h"
#include "CoreModule.h"
#include "CollisionRectangle.h"
#include "CollisionObject.h"
#include "UpdateExecutor.h"


namespace bamf {
    
    class WhoIsExecutor : public SMSPacketExecutor {
        
    private:
        CoreModule * _core;
        
    public:
        WhoIsExecutor(CoreModule * coreModule);
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
    };
    
}

#endif /* defined(__Bamf__WhoIsExecutor__) */
