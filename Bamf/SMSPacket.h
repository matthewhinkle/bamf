//
//  SMSPacket.h
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#ifndef __Bamf__SMSPacket__
#define __Bamf__SMSPacket__

#include <iostream>
#include <stdio.h>
#include "IFixedLengthPacket.h"
#include <assert.h>

namespace bamf {
    
    class SMSPacket : public IFixedLengthPacket {
    private:
        std::string message;
        
    public:
        SMSPacket();
        SMSPacket(std::string message);
        ~SMSPacket();
        
        int getLength();
        IFixedLengthPacket * fromMemoryBlock(void * memoryBlock);
        
        void * asMemoryBlock();
        std::string getMessage();
        
        unsigned char byteAt(int index);
        void writeLongAt(long number, int index);

        static void testSmsPacket() {
            SMSPacket packet = bamf::SMSPacket("Hello world. This can be buffer overflowed.\n");
            SMSPacket * newPacket = (SMSPacket *) packet.fromMemoryBlock(packet.asMemoryBlock());
            assert(packet.getMessage() == newPacket->getMessage());
        }

    };

    
    
}

#endif /* defined(__Bamf__SMSPacket__) */
