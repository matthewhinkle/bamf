//
//  Packet.h
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#ifndef Bamf_Packet_h
#define Bamf_Packet_h

namespace bamf {
    
    class IFixedLengthPacket {
      
    public:
        virtual ~IFixedLengthPacket() {};
        
        virtual int getLength() = 0;
        virtual IFixedLengthPacket * fromMemoryBlock(void * memoryBlock) = 0;
        
        virtual void * asMemoryBlock() = 0;
        
    };
    
}

#endif
