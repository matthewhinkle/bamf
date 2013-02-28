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

namespace bamf {
    
    class UpdateExecutor : public SMSPacketExecutor {
        
    private:
        CoreModule * _core;
        
    public:
        UpdateExecutor(CoreModule * core);
        
        unsigned char packetHeader();
        void executePacket(Socket * sender, SMSPacket * packet);
        
        static SMSPacket * toPacket(BamfObject * object);
        BamfObject * fromPacket(SMSPacket * packet);
        
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
