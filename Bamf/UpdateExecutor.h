//
//  UpdateExecutor.h
//  Bamf
//
//  Created by Mike Hershey on 2/27/13.
//
//

#ifndef __Bamf__UpdateExecutor__
#define __Bamf__UpdateExecutor__

#include <iostream>
#include "SMSPacketExecutor.h"
#include "BamfObject.h"
#include <stdio.h>
#include <string.h>
#include "SpriteObject.h"
#include "CollisionRectangle.h"

namespace bamf {
    
    class UpdateExecutor : public SMSPacketExecutor {
        
    public:
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
        static SMSPacket * toPacket(BamfObject * object);
        static BamfObject * fromPacket(SMSPacket * packet);
        
    };
    
}

#endif /* defined(__Bamf__UpdateExecutor__) */
