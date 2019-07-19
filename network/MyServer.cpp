//
// Created by CHULI on 2019/7/18.
//

#include "MyServer.h"
#include <string>

MyServer::MyServer(EventLoop *loop, int port) : _server(new TcpServer(loop, port))
{
    _server->setConnectionCallback(std::bind(&MyServer::onConnection, this, _1));
    _server->setMessageCallback(std::bind(&MyServer::onMessage, this, _1, _2));
    _server->setCompleteCallback(std::bind(&MyServer::onComplete, this, _1));
}

MyServer::~MyServer()
{
    delete _server;
}

void MyServer::start(int threads)
{
    _server->start(threads);
}

void MyServer::onConnection(TcpConnection *conn)
{
    int clientfd = conn->getSocketfd();
    printf("New Connection fd created: %d\n", clientfd);
}

void MyServer::onComplete(TcpConnection *conn)
{
    int clientfd = conn->getSocketfd();
    printf("Send message complete for fd: %d\n", clientfd);
}

void MyServer::onMessage(TcpConnection *conn, StringBuffer *buffer)
{
    int clientfd = conn->getSocketfd();
    string number = buffer->retrieveAsString();
    try
    {
        int num = stoi(number);
        long result = factorial(num);
        conn->send(to_string(result));
    } catch (...)
    {
        printf("Format error for fd: %d\n", clientfd);
    }
}

long MyServer::factorial(int n) {
    if(n<=0)
        return 0;
    long result = 1;
    for(int i = n; i <= 1, i--)
    {
        result *= result*i;
    }
    retrun result;
}