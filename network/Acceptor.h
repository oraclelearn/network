//
// Created by chuli on 2019/2/11.
//
#include "Socket.h"
#include "Channel.h"
#include "NetworkType.h"

#ifndef NETCONNECT_ACCEPTOR_H
#define NETCONNECT_ACCEPTOR_H


class Acceptor {

    Acceptor(EventLoop *loop, int port);

    ~Acceptor();

    //listen the port
    void listen();

    //handle accept connection
    void handleRead();
    void setNewConnection(NewConnection newConnection);

private:
    //loop pointer
    EventLoop* _loop;

    //socket and channel
    Socket _acceptorSocket;
    Channel _acceptorChannel;

    //callback functions
    NewConnection _newConnection;
};


#endif //NETCONNECT_ACCEPTOR_H
