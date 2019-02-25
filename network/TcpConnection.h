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
    void send();

    //on functions
    void setMessageCallback(MessageCallback msgCallback);

private:
    Channel* _connChannel;
    EventLoop* _loop;

    StringBuffer _inBuffer;
    StringBuffer _outBuffer;

    MessageCallback _messageCallback;

    //functions
    void sendInLoop();
};


#endif //NETWORK_TCPCONNECTION_H
