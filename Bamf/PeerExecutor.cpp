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
        
        int port = informationOf->hostPort;
        std::memcpy(memoryBlock+offset, &port, sizeof(int));
        offset += sizeof(int);
        
        //todo buffer size bounds check.
        std::string hostname = informationOf->getHostName();
        const char * hostnameString = hostname.c_str();
        //std::cout << "hostname is " << strlen(hostnameString) << " long.\n";
        std::memcpy(memoryBlock+offset, hostnameString, strlen(hostnameString));
        
        sendTo->doWrite(memoryBlock, 160);
        delete memoryBlock;
    }
    
    void PeerExecutor::executePacket(Socket * sender, SMSPacket * packet)
    {
        //std::cout << "Got a gossip request";
        for(int i = 0; i < this->_sockets->size(); i++) {
            Socket * socket = (*this->_sockets)[i];
            if(socket == sender) {
                continue;
            }
            sendForSocket(sender, socket);
        }
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        int offset = 0;
        
        char header = 'D';
        std::memcpy(memoryBlock+offset, &header, sizeof(char));
        offset += sizeof(char);
        
        sender->doWrite(memoryBlock, 160);
        delete memoryBlock;
    }
    
    

};