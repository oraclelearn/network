//
// Created by chuli on 2019/2/11.
//

#include "Socket.h"

Socket::Socket() {
    _socketfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (_socketfd < 0) {
        printf("Socket::Socket error");
    }
}

int Socket::fd() {
    return _socketfd;
}

void Socket::bindAddress(const string &IPAddress, const string &IPPort) {
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(IPAddress);
    servaddr.sin_port = htons(IPPort);
    int ret = ::bind(_socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if( ret < 0){
        printf("Socket::bindAddress error");
    }
}

void Socket::listen() {
    int ret = ::listen(_listenfd, SOMAXCONN);
    if(ret <0){
        printf("Socket::listen error");
    }
}