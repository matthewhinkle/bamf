//
//  PingExecutor.h
//  Bamf
//
//  Created by Mike Hershey on 2/27/13.
//
//

#ifndef __Bamf__PingExecutor__
#define __Bamf__PingExecutor__

#include <iostream>
#include "SMSPacketExecutor.h"

namespace bamf {
    
    class PingExecutor : public SMSPacketExecutor {
      
    public:
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
    };
    
}

#endif /* defined(__Bamf__PingExecutor__) */
