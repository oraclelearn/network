//
// Created by chuli on 2019/2/20.
//

#ifndef NETWORK_TCPSERVER_H
#define NETWORK_TCPSERVER_H

#include "NetworkType.h"
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "EventLoopThreadPool.h"
#include "Acceptor.h"

class TcpServer
{
public:
    TcpServer(EventLoop *loop, int port);

    ~TcpServer();

    //funcitons
    void start(int num);

    void onConnected(int clientfd);

    void onRemoveConnection(int clientfd);

    //set callback functions
    void setConnectionCallback(ConnectionCallback connCallback);

    void setMessageCallback(MessageCallback msgCallback);

    void setCompleteCallback(CompleteCallback completeCallback);

private:
    //main loop and eventloop threadpool
    EventLoop *_mainLoop;
    EventLoopThreadPool *_workThreadPool;

    //acceptor
    Acceptor *_acceptor;

    //clients connections
    ConnectionMap _connMap;

    //callback functions
    ConnectionCallback _connectionCallback;
    MessageCallback _messageCallback;
    CompleteCallback _completeCallback;
};


#endif //NETWORK_TCPSERVER_H
