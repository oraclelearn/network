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
    ~TcpServer();

    //funcitons
    void start();
    void onConnected(int clientfd);
    void setMessageCallback(MessageCallbak msgCallback);

private:
    EventLoop* _loop;
    Acceptor* _pacceptor;

    MessageCallback _messageCallback;

    //save the connections
    ConnectionMap _connMap;

};


#endif //NETWORK_TCPSERVER_H
