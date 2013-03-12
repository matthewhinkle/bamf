//
//  SyncRequest.h
//  Bamf
//
//  Created by Mike Hershey on 3/11/13.
//
//

#ifndef __Bamf__SyncRequest__
#define __Bamf__SyncRequest__

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
    
    class SyncRequest : public SMSPacketExecutor {
        
    private:
        CoreModule * _core;
        
    public:
        SyncRequest(CoreModule * coreModule);
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
    };
    
}

#endif /* defined(__Bamf__SyncRequest__) */
