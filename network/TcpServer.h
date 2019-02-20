//
// Created by chuli on 2019/2/20.
//

#ifndef NETWORK_TCPSERVER_H
#define NETWORK_TCPSERVER_H

#include "NetworkType.h"
#include "EventLoop.h"

class TcpServer {
public:
    TcpServer(EventLoop* loop, uint16_t port);

private:
    EventLoop* _loop;
    Acceptor* _pacceptor;


};


#endif //NETWORK_TCPSERVER_H
