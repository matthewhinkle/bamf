//
//  PeerConnector.h
//  Bamf
//
//  Created by Mike Hershey on 3/9/13.
//
//

#ifndef __Bamf__PeerConnector__
#define __Bamf__PeerConnector__

#include <iostream>
#include "SMSPacketExecutor.h"
#include "BamfObject.h"
#include <stdio.h>
#include <string.h>
#include "SpriteObject.h"
#include "CoreModule.h"
#include "CollisionRectangle.h"


namespace bamf {
    
    class PeerConnector : public SMSPacketExecutor {
        
    private:
        std::vector<Socket *> * _sockets;
        
    public:
        PeerConnector(std::vector<Socket *> * sockets);
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
    };
    
}

#endif /* defined(__Bamf__PeerConnector__) */
