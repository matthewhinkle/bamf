//
//  SocketConstants.h
//  Bamf
//
//  Created by Mike Hershey on 2/15/13.
//
//

#ifndef Bamf_SocketConstants_h
#define Bamf_SocketConstants_h

#include <sys/types.h>
#include <sys/socket.h>

enum SocketFamily {
      Loopback = AF_LOCAL
    , IPV4 = AF_INET
    , IPV6 = AF_INET6
};

enum SocketType {
      TCP = SOCK_STREAM
    , UDP = SOCK_DGRAM
};

#endif
