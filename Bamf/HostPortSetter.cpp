//
//  HostPortSetter.cpp
//  Bamf
//
//  Created by Mike Hershey on 3/10/13.
//
//

#include "HostPortSetter.h"

namespace bamf {

    HostPortSetter::HostPortSetter()
    {
        
    }

    unsigned char HostPortSetter::packetHeader()
    {
        return 'H';
    }

    void HostPortSetter::executePacket(Socket * sender, SMSPacket * packet)
    {
        char * memory = (char *)packet->asMemoryBlock();
        int offset = sizeof(char);
        
        int port;
        std::memcpy(&port, memory+offset, sizeof(int));
        offset += sizeof(int);
        
        std::cout << "Client has registered that it is listening at " << port << "/n";
        
        sender->hostPort = port;
        
    }

};