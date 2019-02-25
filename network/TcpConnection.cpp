//
// Created by chuli on 2019/2/23.
//

#include "TcpConnection.h"
#include "Channel.h"

TcpConnection::TcpConnection(EventLoop *loop, int clientfd)
        : _loop(loop),
          _connChannel(new Channel(loop, clientfd)) {
    _connChannel->setReadCallback(std::bind(TcpConnection::handleRead, this));
    _connChannel->setWriteCallback(std::bind(TcpConnection::handleWtite, this));
}

void TcpConnection::handleRead() {
    int sockfd = _connChannel->fd();
    char tmpstr[MAX_LINE];
    memset(tmpstr, 0, MAX_LINE);
    int readlength = ::read(sockfd, tmpstr, MAX_LINE);
    if (readlength < 0) {
        if (errno == ECONNRESET) {
            printf("Close socket fd for %d", sockfd);
            ::close(sockfd);
        }
    } else if (readlength == 0) {
        printf("Read 0 from fd %d", sockfd);
        ::close(sockfd);
    } else {
        string line(tmpstr, readlength);
        _inBuffer.append(line);
        //call the user functions
        _messageCallback(this, _inBuffer);
    }
}


void TcpConnection::setMessageCallback(MessageCallback msgCallback) {
    _messageCallback = msgCallback;
}

void TcpConnection::handleWtite() {

}