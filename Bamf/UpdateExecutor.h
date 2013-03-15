//
//  UpdateExecutor.h
//  Bamf
//
//  Created by Mike Hershey on 2/27/13.
//
//

#ifndef __Bamf__UpdateExecutor__
#define __Bamf__UpdateExecutor__

#include <iostream>
#include "SMSPacketExecutor.h"
#include "BamfObject.h"
#include <stdio.h>
#include <string.h>
#include "SpriteObject.h"
#include "CoreModule.h"
#include "CollisionRectangle.h"
#include "WhoIs.h"

namespace bamf {
    
    class NetworkingModule;
    
    class UpdateExecutor : public SMSPacketExecutor {
        
    private:
        CoreModule * _core;
        NetworkingModule * _module;
        
    public:
        UpdateExecutor(CoreModule * core, NetworkingModule * networking);
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
        static SMSPacket * toPacket(Scene * scene, BamfObject * object);
        
        static void test(BamfObject * object)
        {
            /*
            SMSPacket * packet = toPacket(object);
            BamfObject * newObject = fromPacket(packet);
             */
        }
    };
    
}

#endif /* defined(__Bamf__UpdateExecutor__) */
