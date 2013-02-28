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
    
    SMSPacket::SMSPacket(std::string message)
    {
        this->message = message;
    }
    
    SMSPacket::~SMSPacket()
    {
        
    }

    int SMSPacket::getLength()
    {
        return 160;
    }
    
    unsigned char SMSPacket::byteAt(int index)
    {
        void * memory = this->asMemoryBlock();
        char * charArray = (char *) memory;
        unsigned char character = charArray[index];
        free(memory);
        return character;
    }
    
    void SMSPacket::writeLongAt(long number, int index)
    {
        this->message[index] = number & 0xff;
        this->message[index+1] = (number>>8)  & 0xff;
        this->message[index+2] = (number>>16) & 0xff;
        this->message[index+3] = (number>>24) & 0xff;
        //TODO
    }

    void * SMSPacket::asMemoryBlock() {
        //trust me compiler ;) this is totally reasonable. what a fantastic language.
        void * ret = (void*) calloc(this->getLength(),sizeof(char));
        std::strcpy ((char*)ret, this->message.c_str());
        return ret;
    }

    IFixedLengthPacket * SMSPacket::fromMemoryBlock(void * memoryBlock) {
        std::string message = std::string((char *)memoryBlock);
        return new SMSPacket(message);
    }
    
    std::string SMSPacket::getMessage()
    {
        return this->message;
    }
    
}