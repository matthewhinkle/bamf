//
//  SMSPacketDispatcher.h
//  Bamf
//
//  Created by Mike Hershey on 2/22/13.
//
//

#ifndef __Bamf__SMSPacketDispatcher__
#define __Bamf__SMSPacketDispatcher__

#include <iostream>
#include "SMSPacket.h"
#include "SMSPacketExecutor.h"
#include "Socket.h"
#include <vector>

#import "PingExecutor.h"

namespace bamf {
    
    class SMSPacketDispatcher {
        
    private:
        std::vector<SMSPacketExecutor *> * executors;
        
    public:
        SMSPacketDispatcher();
        
        void registerPacket(SMSPacketExecutor * packetExecutor);
        void dispactPacket(Socket * sender, SMSPacket * packet);
    };
    
}

#endif /* defined(__Bamf__SMSPacketDispatcher__) */
