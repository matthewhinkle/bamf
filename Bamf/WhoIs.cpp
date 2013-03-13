//
//  WhoIs.cpp
//  Bamf
//
//  Created by Mike Hershey on 3/13/13.
//
//

#include "WhoIs.h"

namespace bamf {
  
    WhoIs::WhoIs(CoreModule * core)
    : _core(core)
    {
    }
    
    unsigned char WhoIs::packetHeader()
    {
        return 'w';
    }
    
    void WhoIs::executePacket(bamf::Socket *sender, bamf::SMSPacket *packet)
    {
        //parse our the object id
        char * memory = (char *)packet->asMemoryBlock();
        int offset = sizeof(char);
        
        uint64_t id;
        std::memcpy(&id, memory+offset, sizeof(id));
        offset += sizeof(id);
        
        std::cout << "Received a whois packet for object id: " << id << "\n";
        
        BamfObject * shouldBeSprite = _core->getSceneManager()->getCurrentScene()->getObjectById(id);
        SpriteObject * spriteObject = dynamic_cast<SpriteObject*>(shouldBeSprite);
        if(spriteObject != 0) {
            SMSPacket * whoisResponse = WhoIs::createResponsePacket(spriteObject);
            sender->doWrite(whoisResponse->asMemoryBlock(), whoisResponse->getLength());
            delete whoisResponse;
            SMSPacket * updatePacket = UpdateExecutor::toPacket(_core->getSceneManager()->getCurrentScene(), spriteObject);
            sender->doWrite(updatePacket->asMemoryBlock(), updatePacket->getLength());
            delete updatePacket;
        } else {
            std::cout << "Got a non sprite based object, whois cannot handle those." << "\n";
        }
        
    }
    
    SMSPacket * WhoIs::createResponsePacket(SpriteObject * spriteObject)
    {
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        int offset = 0;
        
        char header = 'W';
        std::memcpy(memoryBlock+offset, &header, sizeof(char));
        offset += sizeof(char);
        
        u_int64_t id = spriteObject->getId();
        std::memcpy(memoryBlock+offset, &id, sizeof(u_int64_t));
        offset += sizeof(u_int64_t);
        
        const char * stringResource = spriteObject->getSprite()->getImageName().c_str();
        std::memcpy(memoryBlock+offset, stringResource, strlen(stringResource));//TODO watch for buffer overflow
        offset += strlen(stringResource);
        
        return new SMSPacket(memoryBlock);
    }
    
    SMSPacket * WhoIs::createRequestPacket(u_int64_t objectID) {
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        int offset = 0;
        
        char header = 'w';
        std::memcpy(memoryBlock+offset, &header, sizeof(char));
        offset += sizeof(char);
        
        u_int64_t id = objectID;
        std::memcpy(memoryBlock+offset, &id, sizeof(u_int64_t));
        offset += sizeof(u_int64_t);
    
        return new SMSPacket(memoryBlock);
    }
    
};