//
//  PacketIO.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#include "PacketIO.h"

namespace bamf
{

    FixedLengthPacketIO::FixedLengthPacketIO(IFixedLengthPacket * templatePacket)
    {
        this->bufferedPackets = new std::vector<IFixedLengthPacket *>();
        this->packetSize = templatePacket->getLength();
        this->templatePacket = templatePacket;
    }

    void FixedLengthPacketIO::onDataRead(void * memoryBlock)
    {
        this->bufferedPackets->push_back(this->templatePacket->fromMemoryBlock(memoryBlock));
    }
    
    IFixedLengthPacket * FixedLengthPacketIO::nextPacket()
    {
        IFixedLengthPacket * ret = (*this->bufferedPackets)[0];
        this->bufferedPackets->erase(this->bufferedPackets->begin());
        return ret;
    }

}