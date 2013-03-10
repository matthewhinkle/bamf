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
#import "PeerExecutor.h"
#import "PeerConnector.h"
#import "HostPortSetter.h"

#include <stdio.h>

namespace bamf {
    
class NetworkingModule : public Module {

private:
    ServerSocket * serverSocket;
    std::vector<Socket *> * sockets;
    SMSPacket * templatePacket;
    SMSPacketDispatcher * dispatch;
    CoreModule * _core;
    bool _hasInited;
    
public:
    NetworkingModule(CoreModule * core);
    
    void init();
	void update(Scene * scene, unsigned delta);
    void sendPacket(SMSPacket * packet);
    
    void initializeNetworkGame(std::string hostname, int port);
    std::vector<Socket *> * getSockets();

};
    
}

#endif /* defined(__Bamf__NetworkingModule__) */
