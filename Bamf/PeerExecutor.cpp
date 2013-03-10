//
//  PeerExecutor.cpp
//  Bamf
//
//  Created by Mike Hershey on 3/9/13.
//
//

#include "PeerExecutor.h"

namespace bamf {

    PeerExecutor::PeerExecutor(std::vector<Socket *> * sockets)
    : _sockets(sockets)
    {
        
    }

    unsigned char PeerExecutor::packetHeader()
    {
        return '?';
    }
    
    void sendForSocket(Socket * sendTo, Socket * informationOf) {
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        int offset = 0;
        
        char header = 'P';
        std::memcpy(memoryBlock+offset, &header, sizeof(char));
        offset += sizeof(char);
        
        int port = informationOf->getPort();
        std::memcpy(memoryBlock+offset, &port, sizeof(int));
        offset += sizeof(int);
        
        //todo buffer size bounds check.
        std::string hostname = informationOf->getHostName();
        std::memcpy(memoryBlock+offset, hostname.c_str(), hostname.size());
        
        sendTo->doWrite(memoryBlock, 160);
    }
    
    void PeerExecutor::executePacket(Socket * sender, SMSPacket * packet)
    {
        for(int i = 0; i < this->_sockets->size(); i++) {
            Socket * socket = (*this->_sockets)[i];
            sendForSocket(sender, socket);
        }
    }
    
    

};