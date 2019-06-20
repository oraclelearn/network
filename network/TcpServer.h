//
// Created by chuli on 2019/2/20.
//

#ifndef NETWORK_TCPSERVER_H
#define NETWORK_TCPSERVER_H

#include "NetworkType.h"
#include "EventLoop.h"

class TcpServer
{
public:
    TcpServer(uint16_t port);

    ~TcpServer();

    //funcitons
    void start();

    void onConnected(int clientfd);

    //set callback functions
    void setConnectionCallback(ConnectionsCallback connCallback);

    void setMessageCallback(MessageCallbak msgCallback);

    void setCompleteCallback(CompleteCallback completeCallback);

private:
    //main loop
    EventLoop *_pmainloop;
    //loop threads for ios
    EventLoopThreadPool *_peventThreadPool;

    //acceptor
    Acceptor *_pacceptor;

    //save the connections
    ConnectionMap _connMap;

    //callback functions
    ConnectionCallback _connectionCallback;
    MessageCallback _messageCallback;
    CompleteCallback _completeCallback;
};


#endif //NETWORK_TCPSERVER_H
