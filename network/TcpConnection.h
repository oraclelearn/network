//
// Created by chuli on 2019/2/23.
//

#ifndef NETWORK_TCPCONNECTION_H
#define NETWORK_TCPCONNECTION_H


class TcpConnection {
public:
    TcpConnection(EventLoop* loop, int clientfd);
    ~TcpConnection();

    //functions
    void handleRead();
    void handleWtite();

private:
    Channel* _connChannel;
    EventLoop* _loop;
};


#endif //NETWORK_TCPCONNECTION_H
