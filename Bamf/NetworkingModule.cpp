//
//  NetworkingModule.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#include "NetworkingModule.h"

namespace bamf {
    
    NetworkingModule::NetworkingModule(CoreModule * core)
    : sockets(new std::vector<Socket *>())
    , templatePacket(new SMSPacket())
    ,dispatch(new SMSPacketDispatcher())
    ,_core(core)
    {
    }
    
    void NetworkingModule::init()
    {
        this->dispatch->registerPacket(new UpdateExecutor(this->_core));
        this->dispatch->registerPacket(new PeerExecutor(this->sockets));
        //first setup our server socket
        this->serverSocket = new ServerSocket(ServerSocket(IPV4, TCP, false));
        this->serverSocket->doBind(0);
        this->serverSocket->doListen();
        std::cout << "Listening for conncetions on port: " << this->serverSocket->boundPort() << "\n";
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
    
    void NetworkingModule::sendPacket(SMSPacket * packet)
    {
        BamfObject * object = _core->getSceneManager()->getCurrentScene()->getObjectById(0);
        if(object != NULL) {
            packet = UpdateExecutor::toPacket(_core->getSceneManager()->getCurrentScene(), object);
            std::cout << "Attempting to send packet updates!!!\n";
            for(int i = 0; i < this->sockets->size(); i++) {
                Socket * socket = (*this->sockets)[i];
                socket->doWrite(packet->asMemoryBlock(), packet->getLength());
            }
        }
    }
    
    std::vector<Socket *> * NetworkingModule::getSockets()
    {
        return this->sockets;
    }
    
    void NetworkingModule::initializeNetworkGame(std::string hostname, int port)
    {
        bamf::Socket * client = new bamf::Socket(IPV4, TCP, false);
        if(!client->doConnect(hostname, port)) {
            std::cout << "Error connecting to seeding peer! aborting.";
            exit(1);
        }
        this->sockets->push_back(client);
        
        
    }
    
    
}