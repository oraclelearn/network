//
// Created by CHULI on 2019/7/18.
//

#ifndef NETWORK_MYSERVER_H
#define NETWORK_MYSERVER_H

#include "TcpServer.h"
#include "TcpConnection.h"

class MyServer
{
public:
    MyServer(EventLoop *loop, int port);

    ~MyServer();

    void start(int threads);

private:
    void onConnection(TcpConnection *conn);

    void onMessage(TcpConnection *conn, StringBuffer *buffer);

    void onComplete(TcpConnection *conn);

    long factorial(int n);

    TcpServer * _server;

};


#endif //NETWORK_MYSERVER_H
