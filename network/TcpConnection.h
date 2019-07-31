//
// Created by chuli on 2019/2/23.
//

#ifndef NETWORK_TCPCONNECTION_H
#define NETWORK_TCPCONNECTION_H

#include "StringBuffer.h"
#include "NetworkType.h"
#include "EventLoop.h"

class TcpConnection {
public:
    TcpConnection(EventLoop *loop, int clientfd);

    ~TcpConnection();

    //event functions
    void connectEstablished();

    //internal handle functions
    void handleRead();

    void handleWrite();

    void handleClose(int socketfd);

    //user functions, user use them to send back message
    void send(const string &msg);

    //callback functions, to call the user callback functions
    void setMessageCallback(MessageCallback msgCallback);

    void setCompleteCallback(CompleteCallback completeCallback);

    void setConnectionCallback(ConnectionCallback connCallback);

    void setCloseCallback(CloseCallback closeCallback);

    //get socketfd
    int getSocketfd();

private:
    EventLoop *_loop;
    Channel *_connChannel;

    StringBuffer _inBuffer;
    StringBuffer _outBuffer;

    //callback functions
    MessageCallback _messageCallback;
    CompleteCallback _completeCallback;
    ConnectionCallback _connCallback;
    CloseCallback _closeCallback;

    //functions
    void sendInLoop(const string &msg);
};


#endif //NETWORK_TCPCONNECTION_H
