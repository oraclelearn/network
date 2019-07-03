//
// Created by chuli on 2019/2/23.
//

#ifndef NETWORK_TCPCONNECTION_H
#define NETWORK_TCPCONNECTION_H

#include "StringBuffer.h"
#include "NetworkType.h"

class TcpConnection
{
public:
    TcpConnection(EventLoop *loop, int clientfd);

    ~TcpConnection();

    //event functions
    void connectEstablished();

    //internal handle functions
    void handleRead();

    void handleWtite();

    void handleClose();

    //callback functions, to call the user callback functions
    void setMessageCallback(MessageCallback msgCallback);

    void setCompleteCallback(CompleteCallback completeCallback);

    void setConnectionCallback(ConnectionCallback connCallback);

    void setCloseCallback(CloseCallback closeCallback);

    //user functions, user use them to send back message
    void send(const string &msg);

private:
    Channel *_connChannel;
    EventLoop *_loop;

    int _clientfd;

    StringBuffer _inBuffer;
    StringBuffer _outBuffer;

    MessageCallback _messageCallback;
    CompleteCallback _completeCallback;
    ConnectionCallback _connCallback;
    CloseCallback _closeCallback;

    //functions
    void sendInLoop(const string &msg);
};


#endif //NETWORK_TCPCONNECTION_H
