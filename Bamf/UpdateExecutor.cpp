//
//  UpdateExecutor.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/27/13.
//
//

#include "UpdateExecutor.h"

namespace bamf {

    unsigned char UpdateExecutor::packetHeader()
    {
        return 'u';
    }
    
    void UpdateExecutor::executePacket(Socket * sender, SMSPacket * packet)
    {
        
    }
    
    SMSPacket * UpdateExecutor::toPacket(BamfObject * object)
    {
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        uint64_t id = object->getId();
        std::memcpy(memoryBlock+1, &id, sizeof(object->getId()));
        return new SMSPacket(memoryBlock);
    }
    
    BamfObject * UpdateExecutor::fromPacket(SMSPacket * packet)
    {
        uint64_t id = -1;
        char * memory = (char *)packet->asMemoryBlock();
        std::memcpy(&id, memory+1, sizeof(id));
        free(memory);
        
        bamf::CollisionRectangle rectangle(glm::vec2(0.0f,300.0f),100.0f,350.0f);
        bamf::ResourceManager man;
        bamf::Sprite sprite("Resources/mage.png");
        sprite.load(man);
        sprite.setHotspot(sprite.getBounds().getCenter());
        bamf::SpriteObject * ret = new SpriteObject(&sprite, &rectangle);
        
        return ret;
    }

}