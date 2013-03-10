//
//  PeerExecutor.h
//  Bamf
//
//  Created by Mike Hershey on 3/9/13.
//
//

#ifndef __Bamf__PeerExecutor__
#define __Bamf__PeerExecutor__

#include <iostream>
#include "SMSPacketExecutor.h"
#include "BamfObject.h"
#include <stdio.h>
#include <string.h>
#include "SpriteObject.h"
#include "CoreModule.h"
#include "CollisionRectangle.h"


namespace bamf {
    
    class PeerExecutor : public SMSPacketExecutor {
        
    private:
        std::vector<Socket *> * _sockets;
        
    public:
        PeerExecutor(std::vector<Socket *> * sockets);
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
    };
    
}


#endif /* defined(__Bamf__PeerExecutor__) */
