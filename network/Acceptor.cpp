//
// Created by chuli on 2019/2/11.
//

#include "Acceptor.h"

Acceptor::Acceptor(EventLoop *loop, int port)
        : _loop(loop),
          _acceptorSocket(),
          _acceptorChannel(loop, acceptorSocket_.fd())
{
    acceptorSocket_.bindAddress(port);
    _acceptorChannel.setReadCallback(std::bind(&Acceptor::handleRead()), this);
}

Acceptor::~Acceptor() {
    _acceptorChannel.disableReading();
    //_acceptorChannel.remove();
}

void Acceptor::listen()
{
    //launch listening
    _acceptorSocket.listen();
    //enable channel reading
    _acceptorChannel.enableReading();
}

void Acceptor::handleRead()
{
    int clientfd = _acceptorSocket.accept();
    if (clientfd > 0)
    {
        //callback Tcpserver::onConnected
        if (_newConnection)
        {
            _newConnection(clientfd);
        } else
        {
            ::close(clientfd);
        }
    }
}

//set callback functions
void Acceptor::setNewConnection(NewConnection newConnection)
{
    _newConnection = newConnection;
}
