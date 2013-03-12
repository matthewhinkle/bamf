//
//  SyncRequest.cpp
//  Bamf
//
//  Created by Mike Hershey on 3/11/13.
//
//

#include "SyncRequest.h"

namespace bamf {
  
    SyncRequest::SyncRequest(CoreModule * coreModule)
    : _core(coreModule)
    {
        
    }
    
    unsigned char SyncRequest::packetHeader() {
        return 's';
    }
    
    void SyncRequest::executePacket(bamf::Socket *sender, bamf::SMSPacket *packet)
    {
        Scene * scene = _core->getSceneManager()->getCurrentScene();
        std::cout << "Sending all object states as request to " << sender->getHostName() << ":" << sender->getPort() << "\n";
        scene->getCollisionLayer()->foreachObject(0, [=](CollisionObject * a, unsigned dt) {
            std::cout << "Sending update information for game object: " << a->getId() << "\n";
            SMSPacket * packet = UpdateExecutor::toPacket(scene, a);
            sender->doWrite(packet->asMemoryBlock(), packet->getLength());
        });
        
        //send the done packet
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        int offset = 0;
        
        char header = 'D';
        std::memcpy(memoryBlock+offset, &header, sizeof(char));
        offset += sizeof(char);
        
        sender->doWrite(memoryBlock, 160);
        delete memoryBlock;
    }
    
};