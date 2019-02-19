//
// Created by chuli on 2019/2/11.
//

#include "Acceptor.h"

Acceptor::Acceptor(EventLoop *loop, const string& IPAddress, const string& IPPort )
        : _loop(loop),
          _acceptorSocket(),
          _acceptorChannel(loop, acceptorSocket_.fd()) {
    acceptorSocket_.bindAddress(IPAddress, IPPort);
    _acceptorChannel.setReadCallback(std::bind(Acceptor::handleRead()),this);
}

void Acceptor::listen() {
    //启动监听
    _acceptorSocket.listen();
    //将channel置为可读
    _acceptorChannel.enableReading();
}

void Acceptor::setNewConnection(NewConnection newConnection) {
    _newConnection = newConnection;
}

void Acceptor::handleRead() {
    struct sockaddr_in clientSockfd;
    int clientfd = _acceptorSocket.accept();
    if(clientfd > 0){
        if(_newConnection){
            _newConnection(clientfd);
        }
        else
        {

        }
    }
}

