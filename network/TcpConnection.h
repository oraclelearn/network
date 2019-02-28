//
// Created by chuli on 2019/2/23.
//

#ifndef NETWORK_TCPCONNECTION_H
#define NETWORK_TCPCONNECTION_H

#include "StringBuffer.h"
#include "NetworkType.h"

class TcpConnection {
public:
    TcpConnection(EventLoop *loop, int clientfd);

    ~TcpConnection();

    //functions
    void handleRead();

    void handleWtite();

    void send(const string &msg);

    //on functions
    void setMessageCallback(MessageCallback msgCallback);
    void setCompleteCallback(CompleteCallback completeCallback);

private:
    Channel *_connChannel;
    EventLoop *_loop;

    StringBuffer _inBuffer;
    StringBuffer _outBuffer;

    MessageCallback _messageCallback;
    CompleteCallback _completeCallback;

    //functions
    void sendInLoop(const string& msg);
};


#endif //NETWORK_TCPCONNECTION_H
