//
//  NetworkingModule.h
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#ifndef __Bamf__NetworkingModule__
#define __Bamf__NetworkingModule__

#include <iostream>
#include "Module.h"
#include "Socket.h"
#include <vector>
#include "SMSPacket.h"
#include "SMSPacketDispatcher.h"
#include "CoreModule.h"
#include "UpdateExecutor.h"

#include <stdio.h>

namespace bamf {
    
class NetworkingModule : public Module {

private:
    ServerSocket * serverSocket;
    std::vector<Socket *> * sockets;
    SMSPacket * templatePacket;
    SMSPacketDispatcher * dispatch;
    CoreModule * _core;
    static NetworkingModule * _instance;
    
public:
    NetworkingModule(CoreModule * core);
    
    void init();
		void update(Scene * scene, unsigned delta);
        void sendPacket(SMSPacket * packet);
    
        static NetworkingModule * getInstance() { return _instance;};
        void setInstance(NetworkingModule * instance) { _instance = instance;}
};
    
}

#endif /* defined(__Bamf__NetworkingModule__) */
