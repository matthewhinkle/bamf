//
//  PingExecutor.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/27/13.
//
//

#include "PingExecutor.h"

namespace bamf {
    
    unsigned char PingExecutor::packetHeader() {
        return 'p';
    }
    
    void PingExecutor::executePacket(Socket * sender, SMSPacket * packet)
    {
        char buffer[160];
        sprintf(buffer, "pPONG");
        
        SMSPacket * response = new SMSPacket(buffer);
        response->writeLongAt(17347347377343, 5);
        
        sender->doWrite(response->asMemoryBlock(), packet->getLength()) ;
    }
    
}