//
//  UpdateExecutor.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/27/13.
//
//

#include "UpdateExecutor.h"

namespace bamf {

    UpdateExecutor::UpdateExecutor(CoreModule * core)
    : _core(core)
    {
        
    }
    
    unsigned char UpdateExecutor::packetHeader()
    {
        return 'u';
    }
    
    void UpdateExecutor::executePacket(Socket * sender, SMSPacket * packet)
    {
        this->fromPacket(packet);
    }
    
    SMSPacket * UpdateExecutor::toPacket(BamfObject * object)
    {
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        int offset = 0;
        
        char header = 'u';
        std::memcpy(memoryBlock+offset, &header, sizeof(char));
        offset += sizeof(char);
        
        uint64_t id = object->getId();
        std::memcpy(memoryBlock+offset, &id, sizeof(id));
        offset += sizeof(id);
        
        float positionX = object->getRigidBody()->getPosition().x;
        std::memcpy(memoryBlock+offset, &positionX, sizeof(positionX));
        offset += sizeof(positionX);
        
        float positionY = object->getRigidBody()->getPosition().y;
        std::memcpy(memoryBlock+offset, &positionY, sizeof(positionY));
        offset += sizeof(positionY);
        
        return new SMSPacket(memoryBlock);
    }
    
    BamfObject * UpdateExecutor::fromPacket(SMSPacket * packet)
    {
        char * memory = (char *)packet->asMemoryBlock();
        int offset = sizeof(char);
        
        uint64_t id;
        std::memcpy(&id, memory+offset, sizeof(id));
        offset += sizeof(id);
        
        float positionX;
        std::memcpy(&positionX, memory+offset, sizeof(positionX));
        offset += sizeof(positionX);
        
        float positionY;
        std::memcpy(&positionY, memory+offset, sizeof(positionY));
        offset += sizeof(positionY);
        
        std::cout << "Received an update! ID: " << id << "@[" << positionX << "," << positionY << "]" << "\n";
        
        free(memory);
        
        BamfObject * object = _core->getSceneManager()->getCurrentScene()->getObjectById(id);
        
        if(object == NULL) {
            std::cout << "not applying update for object id " << id << " because no object in scene has that id.";
        } else {
            object->getRigidBody()->setPositon(glm::vec2(positionX, positionY));
        }
        
        return NULL;
    }

}