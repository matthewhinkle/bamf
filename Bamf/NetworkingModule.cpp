//
//  NetworkingModule.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#include "NetworkingModule.h"

namespace bamf {
    
    NetworkingModule::NetworkingModule()
    : sockets(new std::vector<Socket *>())
    , templatePacket(new SMSPacket())
    ,dispatch(new SMSPacketDispatcher())
    {
    }
    
    void NetworkingModule::init()
    {
        //first setup our server socket
        this->serverSocket = new ServerSocket(ServerSocket(IPV4, TCP, false));
        this->serverSocket->doBind(1337);
        this->serverSocket->doListen();
    }
    
    void NetworkingModule::update(Scene * scene, unsigned delta)
    {
        //first check and see if the server socket has any connections
        Socket * socket = this->serverSocket->doAccept();
        if(socket != NULL) {
            this->sockets->push_back(socket);
            std::cout << "Got a new socket connection!\n";
        }
        for(int i = 0; i < this->sockets->size(); i++) {
            Socket * socket = (*this->sockets)[i];
            while(socket->bytesAvailable() >= 160) {
                void * memoryBlock = calloc(160,sizeof(char));
                socket->doRead(memoryBlock, 160);
                SMSPacket * packet = (SMSPacket *) this->templatePacket->fromMemoryBlock(memoryBlock);
                this->dispatch->dispactPacket(socket, packet);
            }
        }
    }
    
}