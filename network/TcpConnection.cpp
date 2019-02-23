//
// Created by chuli on 2019/2/23.
//

#include "TcpConnection.h"
#include "Channel.h"

TcpConnection::TcpConnection(EventLoop *loop, int clientfd)
        : _loop(loop),
          _connChannel(new Channel(loop, clientfd)) {
    _connChannel->setReadCallback(std::bind(TcpConnection::handleRead, this));
    _connChannel->setWriteCallback(std::bind(TcpConnection::handleWtite, this));
}

void TcpConnection::handleRead(){
    int sockfd = _connChannel->fd();

}
void TcpConnection::handleWtite(){

}