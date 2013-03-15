//
//  WhoIs.h
//  Bamf
//
//  Created by Mike Hershey on 3/13/13.
//
//

#ifndef __Bamf__WhoIs__
#define __Bamf__WhoIs__

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
#include "WhoIsExecutor.h"


namespace bamf {
    
    class WhoIs : public SMSPacketExecutor {
        
    private:
        CoreModule * _core;
        
    public:
        WhoIs(CoreModule * coreModule);
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
        static SMSPacket * createRequestPacket(u_int64_t objectID);
        static SMSPacket * createResponsePacket(SpriteObject * spriteObject);
        
    };
    
}

#endif /* defined(__Bamf__WhoIs__) */
