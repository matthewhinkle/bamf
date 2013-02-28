//
//  Socket.cpp
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#include "Socket.h"

namespace bamf {
    
    Socket::Socket(int fd) {
        this->sockfd = fd;
    }
    
    Socket::Socket(SocketFamily socketFamily, SocketType socketType, bool blocking) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Error opening socket");
            exit(1);
        }
    }
    
    bool Socket::doConnect(std::string hostname, int port)
    {
        struct hostent *server;
        struct sockaddr_in serv_addr;
        server = gethostbyname(hostname.c_str());
        if (server == NULL) {
            return false;
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(port);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            return false;
        return true;
    }
    
    ssize_t Socket::doWrite(void *buf, size_t count)
    {
        return write(this->sockfd, buf, count);
    }
    
    ssize_t Socket::doRead(void *buf, size_t count)
    {
        return read(this->sockfd, buf, count);
    }
    
    size_t Socket::bytesAvailable() {
        int count;
        ioctl(this->sockfd, FIONREAD, &count);
        return count;
    }
    
    ServerSocket::ServerSocket(SocketFamily socketFamily, SocketType socketType, bool blocking) {
        this->blocking = blocking;
        this->sockfd = socket(socketFamily, socketType, 0);
        if(this->sockfd < 0) {
            perror("Error opening up the socket!");
            exit(1);
        }
        if(fcntl(this->sockfd, F_SETFL, O_NONBLOCK) < 0) {
            perror("Error going to non blocking mode!!!");
            exit(1);
        }
    }
    
    ServerSocket::~ServerSocket() {
        
    }
    
    /**
     * Binds to the given port and listens for incoming connections.
     */
    bool ServerSocket::doBind(int port) {
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
        if (bind(this->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("Error binding to port");
            exit(1);
        }
        return true;
    }
    
    /**
     * Starts listening for new connections.
     */
    bool ServerSocket::doListen() {
        if(listen(this->sockfd, 10) < 0) {
            perror("Error listening");
            exit(1);
        }
        return true;
    }
    
    /**
     * Returns a new connected socket. Will block is blocking = true was supplied to the constructor
     */
    Socket * ServerSocket::doAccept() {
        struct sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);
        int newsockfd = accept(this->sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            return NULL;
        }
        return new Socket(newsockfd);
    }
    
}