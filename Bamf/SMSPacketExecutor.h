//
//  SMSPacketExecutor.h
//  Bamf
//
//  Created by Mike Hershey on 2/22/13.
//
//

#ifndef __Bamf__SMSPacketExecutor__
#define __Bamf__SMSPacketExecutor__

#include <iostream>
#include "SMSPacket.h"
#include "Socket.h"

namespace bamf {
    
    class SMSPacketExecutor {
        
    public:
        virtual ~SMSPacketExecutor() {};
        
        virtual unsigned char packetHeader() = 0;
        virtual void executePacket(Socket * sender, SMSPacket * packet) = 0;
    };

}

#endif /* defined(__Bamf__SMSPacketExecutor__) */
