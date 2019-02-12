//
// Created by chuli on 2019/2/11.
//

#ifndef NETCONNECT_ACCEPTOR_H
#define NETCONNECT_ACCEPTOR_H


class Acceptor {

    Acceptor(EventLoop *loop, const InetAddress &listenAddr);

    ~Acceptor();

    //listen the port
    void listen();

    //handle accept connection
    void handleRead();

private:
    //loop pointer
    EventLoop* _loop;

    //socket and channel
    Socket _acceptorSocket;
    Channel _acceptorChannel;
};


#endif //NETCONNECT_ACCEPTOR_H
