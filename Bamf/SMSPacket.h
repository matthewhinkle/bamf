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
        char * memoryBlock;
        
    public:
        SMSPacket();
        SMSPacket(void * memory);
        ~SMSPacket();
        
        int getLength();
        IFixedLengthPacket * fromMemoryBlock(void * memoryBlock);
        
        void * asMemoryBlock();
        
        unsigned char byteAt(int index);
        void writeLongAt(long number, int index);

    };

    
    
}

#endif /* defined(__Bamf__SMSPacket__) */
