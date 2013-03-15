//
//  SMSPacket.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#include "SMSPacket.h"

namespace bamf {

    SMSPacket::SMSPacket() {
        
    }
    
    SMSPacket::~SMSPacket()
    {
        delete this->memoryBlock;
    }
    
    SMSPacket::SMSPacket(void * memory)
    {
        this->memoryBlock = (char*)memory;
    }

    int SMSPacket::getLength()
    {
        return 160;
    }
    
    unsigned char SMSPacket::byteAt(int index)
    {
        char * memory = this->memoryBlock;
        unsigned char character = memory[index];
        return character;
    }
    
    void SMSPacket::writeLongAt(long number, int index)
    {
        this->memoryBlock[index] = number & 0xff;
        this->memoryBlock[index+1] = (number>>8)  & 0xff;
        this->memoryBlock[index+2] = (number>>16) & 0xff;
        this->memoryBlock[index+3] = (number>>24) & 0xff;
        //TODO
    }

    void * SMSPacket::asMemoryBlock() {
        return this->memoryBlock;
    }

    IFixedLengthPacket * SMSPacket::fromMemoryBlock(void * memoryBlock) {
        return new SMSPacket(memoryBlock);
    }
    
}