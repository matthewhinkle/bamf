//
//  SMSPacketDispatcher.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/22/13.
//
//

#include "SMSPacketDispatcher.h"

namespace bamf {
    
    SMSPacketDispatcher::SMSPacketDispatcher() {
        this->executors = new std::vector<SMSPacketExecutor *>();
        this->executors->push_back(new PingExecutor());
    }
    
    void SMSPacketDispatcher::registerPacket(SMSPacketExecutor * packetExecutor)
    {
        this->executors->push_back(packetExecutor);
    }
    
    void SMSPacketDispatcher::dispactPacket(Socket * sender, SMSPacket * packet)
    {
        for(int i = 0; i < this->executors->size(); i++) {
            SMSPacketExecutor * e = (*this->executors)[1];
            if(e->packetHeader() == packet->byteAt(0)) {
                e->executePacket(sender, packet);
            }
        }
    }
    
}