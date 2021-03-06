//
// Created by CHULI on 2019/7/18.
//

#include "MyServer.h"
#include <string>

MyServer::MyServer(EventLoop *loop, int port) : _server(new TcpServer(loop, port))
{
    _server->setConnectionCallback(std::bind(&MyServer::onConnection, this, placeholders::_1));
    _server->setMessageCallback(std::bind(&MyServer::onMessage, this, placeholders::_1, placeholders::_2));
    _server->setCompleteCallback(std::bind(&MyServer::onComplete, this, placeholders::_1));
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
        long long result = factorial(num);
        conn->send(to_string(result)+"\n");
    } catch (...)
    {
        printf("Format error for fd: %d\n", clientfd);
    }
}

long long MyServer::factorial(int n)
{
    printf("The receiving number is %d\n", n);
    if (n <= 0)
    {
        return 0;
    }
    long long result = 1;
    for (int i = n; i >= 1; i--)
    {
        result *= i;
        //printf("i = %d, result = %lld\n", i, result);
    }
    printf("The result number is %lld\n", result);
    return result;
}