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

void TcpConnection::handleWtite() {
    int sockfd = _connChannel->fd();
    if (_connChannel->isWritingCapable()) {
        int writelength = ::write(sockfd, _outBuffer.peek(),_outBuffer.readableBytes());
        if(writelength > 0){
            _outBuffer.retrieve(writelength);
            if(_outBuffer.readableBytes() == 0){
                _connChannel->disableWriting();
            }
        }
    }
}

void TcpConnection::send(const string& msg) {
    sendInLoop(msg);
}

void TcpConnection::sendInLoop(const string &msg) {
    int writelen = 0;
    int sockfd = _connChannel->fd();
    //if buffer is empty, write directly
    if(_outBuffer.readableBytes() == 0){
        int writelength = ::write(sockfd, msg.c_str(), msg.size());
    }
    //after write, there is something left
    if(writelen< msg.size()){
        _outBuffer.append(msg.substr(writelen, msg.size()));
        if(!_connChannel->isWritingCapable()){
            _connChannel->enableWriting();
        }

    }
}


void TcpConnection::setMessageCallback(MessageCallback msgCallback) {
    _messageCallback = msgCallback;
}

void TcpConnection::handleWtite() {

}