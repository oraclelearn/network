//
// Created by chuli on 2019/2/20.
//

#include "TcpServer.h"
#include "Acceptor.h"
void TcpServer::TcpServer(EventLoop *loop, uint16_t port)
:_loop(loop),
_pacceptor(new Acceptor(loop, port))
{
    _pacceptor->setNewConnection(std::bind(TcpServer::onConnected, this, _1));
}

void TcpServer::start() {
    _pacceptor->listen();
}

void TcpServer::onConnected(int clientfd) {
    TcpConnection* conn = new TcpConnection(_loop, clientfd);
    _connMap[clientfd] = conn;
    //set the callback functions

}