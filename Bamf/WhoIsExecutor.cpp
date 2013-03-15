//
//  WhoIsExecutor.cpp
//  Bamf
//
//  Created by Mike Hershey on 3/13/13.
//
//

#include "WhoIsExecutor.h"

namespace bamf {
  
    WhoIsExecutor::WhoIsExecutor(CoreModule * coreModule)
    : _core(coreModule)
    {
        
    }
    
    unsigned char WhoIsExecutor::packetHeader()
    {
        return 'W';
    }
    
    void WhoIsExecutor::executePacket(bamf::Socket *sender, bamf::SMSPacket *packet)
    {
        //parse the packet
        char * memory = (char *)packet->asMemoryBlock();
        int offset = sizeof(char);
        
        uint64_t id;
        std::memcpy(&id, memory+offset, sizeof(id));
        offset += sizeof(id);
        
        char * resourceName = (char*)calloc(160-offset-1, sizeof(char));
        std::memcpy(resourceName, memory+offset, 160-offset-1);
        
        std::cout << "Got information about a new object: " << id << " (" << resourceName << ")" << "\n";
        
        bamf::ResourceManager * man = bamf::ResourceManager::getInstance();
        bamf::Sprite * sprite = new bamf::Sprite(resourceName);
        sprite->load(*man);
        sprite->setHotspot(sprite->getBounds().getCenter());
        bamf::SpriteObject * spriteSprite = new bamf::SpriteObject(sprite, id, false);
        _core->getSceneManager()->getCurrentScene()->addObjectWithZValue(spriteSprite, bamf::Scene::kForegroundMidLayer);
    }
    
};