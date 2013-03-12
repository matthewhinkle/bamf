//
//  PeerConnector.cpp
//  Bamf
//
//  Created by Mike Hershey on 3/9/13.
//
//

#include "PeerConnector.h"

namespace bamf {

    PeerConnector::PeerConnector(std::vector<Socket *> * sockets)
    : _sockets(sockets)
    {
        
    }

    unsigned char PeerConnector::packetHeader()
    {
        return 'P';
    }
    
    void PeerConnector::executePacket(Socket * sender, SMSPacket * packet)
    {
        char * memory = (char *)packet->asMemoryBlock();
        int offset = sizeof(char);
        
        int port;
        std::memcpy(&port, memory+offset, sizeof(int));
        offset += sizeof(int);
        
        char * hostname = (char*)calloc(160-offset-1, sizeof(char));
        std::memcpy(hostname, memory+offset, 160-offset-1);
        
        std::cout << "Got a request to connect to: " << hostname << port << "\n";
        
        bamf::Socket * client = new bamf::Socket(IPV4, TCP, false);
        if(!client->doConnect(hostname, port)) {
            std::cout << "Error connecting to seeding peer! aborting.";
            exit(1);
        }
        this->_sockets->push_back(client);
        delete hostname;
    }
    
};