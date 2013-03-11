//
//  Socket.h
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#ifndef __Bamf__Socket__
#define __Bamf__Socket__

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "SocketConstants.h"
#include <netdb.h> 
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


namespace bamf {

    class Socket {
    private:
        int sockfd;
        bool blocking;
    public:
        std::string hostname;
        int port;
        int hostPort;
        Socket(int fd);
        Socket(SocketFamily socketFamily, SocketType socketType, bool blocking);
        bool doConnect(std::string hostname, int port);
        
        ssize_t doWrite(void *buf, size_t count);
        ssize_t doRead(void *buf, size_t count);
        
        std::string getHostName();
        int getPort();
        
        size_t bytesAvailable();
    };

    class ServerSocket {
    private:
        int sockfd;
        bool blocking;
    public:
        ServerSocket(SocketFamily socketFamily, SocketType socketType, bool blocking);
        ~ServerSocket();
        
        /**
          * Binds to the given port and listens for incoming connections.
          */
        bool doBind(int port);
        
        /**
          * Starts listening for new connections.
          */
        bool doListen();
        
        /**
          * Returns a new connected socket. Will block is blocking = true was supplied to the constructor
          */
        Socket * doAccept();
        
        int boundPort();

        static void test() {
            ServerSocket * socket = new ServerSocket(ServerSocket(IPV4, TCP, false));
            socket->doBind(1337);
            socket->doListen();
            socket->doAccept();
            
            Socket * client = new Socket(IPV4, TCP, false);
            client->doConnect("localhost", 1337);
            client->doWrite((void*)"I am a banana", strlen("I am a banana"));
            
            Socket * serverSide = socket->doAccept();
            if(serverSide == NULL) {
                std::cout << "didn't connect!!!";
            } else {
                void * memory = malloc(strlen("I am a banana"));
                serverSide->doRead(memory, 100);
                //std::cout << (char *) memory;
            }
        }

    };
        
}

#endif /* defined(__Bamf__Socket__) */
