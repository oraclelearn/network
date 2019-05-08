//
// Created by chuli on 2019/2/11.
//

#include "Acceptor.h"

Acceptor::Acceptor(EventLoop *loop, uint16_t port)
        : _loop(loop),
          _acceptorSocket(),
          _acceptorChannel(loop, acceptorSocket_.fd()) {
    acceptorSocket_.bindAddress(port);
    _acceptorChannel.setReadCallback(std::bind(Acceptor::handleRead()), this);
}

void Acceptor::listen() {
    //launch listening
    _acceptorSocket.listen();
    //enable channel reading
    _acceptorChannel.enableReading();
}

void Acceptor::setNewConnection(NewConnection newConnection) {
    _newConnection = newConnection;
}

void Acceptor::handleRead() {
    struct sockaddr_in clientSockfd;
    int clientfd = _acceptorSocket.accept();
    if (clientfd > 0) {
        if (_newConnection) {
            _newConnection(clientfd);
        } else {
            ::close(clientfd);
        }
    }
}

