//
//  PacketIO.h
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#ifndef __Bamf__PacketIO__
#define __Bamf__PacketIO__

#include <iostream>
#include <stdio.h>
#include <vector>
#include <assert.h>

#include "IFixedLengthPacket.h"
#include "SMSPacket.h"

namespace bamf
{

    class FixedLengthPacketIO {
        
    private:
        IFixedLengthPacket * templatePacket;
        std::vector<IFixedLengthPacket *> * bufferedPackets;
        int packetSize;
        
    public:
        FixedLengthPacketIO(IFixedLengthPacket * templatePacket);
        
        void onDataRead(void * memoryBlock);
        IFixedLengthPacket * nextPacket();
    
        static void test() {
            FixedLengthPacketIO * pio = new FixedLengthPacketIO(new SMSPacket());
            pio->onDataRead(SMSPacket("Some data here").asMemoryBlock());
            assert(((SMSPacket*)pio->nextPacket())->getMessage() == "Some data here");
        }
        
    };
}

#endif /* defined(__Bamf__PacketIO__) */
