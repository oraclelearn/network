//
// Created by chuli on 2019/2/20.
//

#include "TcpServer.h"
#include "Acceptor.h"

//TcpServer constructor and destructor
TcpServer::TcpServer(EventLoop *loop, int port) : _mainLoop(loop),
                                                  _workThreadPool(new EventLoopThreadPool(loop)),
                                                  _acceptor(new Acceptor(loop), port),
                                                  _connectionCallback(NULL),
                                                  _completeCallback(NULL),
                                                  _messageCallback(NULL)
{
    _acceptor->setNewConnection(std::bind(&TcpServer::onConnected, this, _1));
}

TcpServer::~TcpServer()
{
    //delete the TcpConnections
    for (ConnectionMapIter iter : _connMap)
    {
        delete iter.second;
    }

    //delete the acceptor
    delete _acceptor;

    //delte the workThreadPool
    delete _workThreadPool;
}

//start the server
void TcpServer::start(int num)
{
    //start the worker thread
    _workThreadPool->setNumThreads(num);
    _workThreadPool->start();
    //start the listener
    _acceptor->listen();
}

void TcpServer::onConnected(int clientfd)
{
    //get the workthread from pool
    EventLoop *ioLoop = _workThreadPool->getNextEventLoop();

    //save the tcp connection into map
    TcpConnection * conn = new TcpConnection(ioLoop, clientfd);
    _connMap[clientfd] = conn;

    //set the callback functions
    conn->setConnectionCallback(_connectionCallback);
    conn->setMessageCallback(_messageCallback);
    conn->setCompleteCallback(_completeCallback);
    conn->setCloseCallback(std::bind(&TcpConnection::onRemoveConnection, this, _1));

    //call the connection established
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}

void TcpServer::onRemoveConnection(int clientfd)
{
    _mainLoop->runInLoop(std::bind(&TcpServer::onRemoveInLoop, this, clientfd));
}

void TcpServer::onRemoveInLoop(int clientfd)
{
    //delete the connection from map
    TcpConnection * conn = _connMap[clientfd];
    if (conn != null)
    {
        _connMap.erase(clientfd);
        //delete the connection
        ::close(clientfd);
        delete conn;
    }
}

//set the user callback functions
void TcpServer::setConnectionCallback(ConnectionCallback connCallback)
{
    _connectionCallback = connCallback;
}

void TcpServer::setMessageCallback(MessageCallback msgCallback)
{
    _messageCallback = msgCallback;
}

void TcpServer::setCompleteCallback(CompleteCallback completeCallback)
{
    _completeCallback = completeCallback;
}




