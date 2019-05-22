//
// Created by chuli on 2019/2/20.
//

#include "TcpServer.h"
#include "Acceptor.h"

void TcpServer::TcpServer(uint16_t port){
    _pmainloop = new EventLoop();
    _pacceptor = new Acceptor(_pmainloop, port);
    _pacceptor->setNewConnection(std::bind(TcpServer::onConnected, this, _1));
}

void TcpServer::start() {
    //start the main loop
    _pmainloop->loop();
    //active the listener socket
    _pacceptor->listen();
}

//set the user callback functions
void TcpServer::setMessageCallback(MessageCallbak msgCallback){
    _messageCallback = msgCallback;
}

void TcpServer::setCompleteCallback(CompleteCallback completeCallback) {
    _completeCallback = completeCallback;
}

void TcpServer:;setConnectionCallback(ConnectionsCallback connCallback){
    _connectionCallback = connCallback;
}

//bind to
void TcpServer::onConnected(int clientfd) {
    TcpConnection * conn = new TcpConnection(_pmainloop, clientfd);
    _connMap[clientfd] = conn;
    //set the callback functions
    conn->setConnectionCallback(_connectionCallback);
    conn->setMessageCallback(_messageCallback);
    conn->setCompleteCallback(_completeCallback);

    //call the connection established
    _pmainloop->runInLoop(std:;bind(TcpConnection::connectEstablished, conn));
}

