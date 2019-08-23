//
// Created by chuli on 2019/2/11.
//

#include "Socket.h"
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <memory.h>

Socket::Socket()
{
    _socketfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (_socketfd < 0)
    {
        printf("Socket::Socket error\n");
    }
}

int Socket::fd()
{
    return _socketfd;
}

void Socket::bindAddress(uint16_t port)
{
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    int ret = ::bind(_socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (ret < 0)
    {
        printf("Socket::bindAddress error\n");
    }
}

void Socket::listen()
{
    int ret = ::listen(_socketfd, SOMAXCONN);
    if (ret < 0)
    {
        printf("Socket::listen error\n");
    }
}

int Socket::accept()
{
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(clientaddr));
    socklen_t clilen = sizeof(struct sockaddr_in);
    int connfd = ::accept(_socketfd, (sockaddr * ) & clientaddr, (socklen_t * ) &clilen);
    if (connfd > 0)
    {
        printf("new connection from client [%s] [%d]\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
    } else
    {
        printf("Socket::accept error\n");
    }
    return connfd;
}