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
    
    SMSPacket * UpdateExecutor::toPacket(Scene * scene, BamfObject * object)
    {
        char * memoryBlock = (char *)calloc(160, sizeof(char));
        int offset = 0;
        
        char header = 'u';
        std::memcpy(memoryBlock+offset, &header, sizeof(char));
        offset += sizeof(char);
        
        uint64_t id = object->getId();
        std::memcpy(memoryBlock+offset, &id, sizeof(id));
        offset += sizeof(id);
        
        float positionX = object->getPosition().x;
        std::memcpy(memoryBlock+offset, &positionX, sizeof(positionX));
        offset += sizeof(positionX);
        
        float positionY = object->getPosition().y;
        std::memcpy(memoryBlock+offset, &positionY, sizeof(positionY));
        offset += sizeof(positionY);
        
        CollisionObject * co = scene->getCollisionLayer()->getObjectById(object->getId());
        float velocityX =  co->getRigidBody()->getLinearVeloctiy().x;
        std::memcpy(memoryBlock+offset, &velocityX, sizeof(velocityX));
        offset += sizeof(velocityX);
        
        float velocityY =  co->getRigidBody()->getLinearVeloctiy().y;
        std::memcpy(memoryBlock+offset, &velocityY, sizeof(velocityY));
        offset += sizeof(velocityY);
        
        for(int i = 0; i < 160; i++) {
            std::cout << memoryBlock[i];
        }
        std::cout << "\n";
        
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
        
        float velocityX;
        std::memcpy(&velocityX, memory+offset, sizeof(velocityX));
        offset += sizeof(velocityX);

        float velocityY;
        std::memcpy(&velocityY, memory+offset, sizeof(velocityY));
        offset += sizeof(velocityY);
        
        std::cout << "Received an update! ID: " << id << "@[" << positionX << "," << positionY << "]   v->[" << velocityX << "," << velocityY << "]" << "\n";
        
        CollisionObject * co = _core->getSceneManager()->getCurrentScene()->getCollisionLayer()->getObjectById(id);
        if(co == NULL) {
            std::cout << "not applying update for object id " << id << " because no object in scene has that id.";
        } else {
            co->getRigidBody()->setPositon(glm::vec2(positionX, positionY));
            co->getRigidBody()->setLinearVeloctiy(glm::vec2(velocityX, velocityY));
        }
        
        return NULL;
    }

}