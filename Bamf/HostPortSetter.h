//
//  HostPortSetter.h
//  Bamf
//
//  Created by Mike Hershey on 3/10/13.
//
//

#ifndef __Bamf__HostPortSetter__
#define __Bamf__HostPortSetter__

#include <iostream>
#include "SMSPacketExecutor.h"
#include "BamfObject.h"
#include <stdio.h>
#include <string.h>
#include "SpriteObject.h"
#include "CoreModule.h"
#include "CollisionRectangle.h"


namespace bamf {
    
    class HostPortSetter : public SMSPacketExecutor {
        
    private:
        
    public:
        HostPortSetter();
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
    };
    
}

#endif /* defined(__Bamf__HostPortSetter__) */
