//
// Created by chuli on 2019/2/23.
//

#include "TcpConnection.h"
#include "Channel.h"
#include "EventLoop.h"
#include <netinet/in.h>
#include <netinet/tcp.h>

TcpConnection::TcpConnection(EventLoop *loop, int clientfd)
        : _loop(loop),
          _connChannel(new Channel(loop, clientfd))
{
    _connChannel->setReadCallback(std::bind(TcpConnection::handleRead, this));
    _connChannel->setWriteCallback(std::bind(TcpConnection::handleWtite, this));
}

//when client send data to server
void TcpConnection::handleRead()
{
    int sockfd = _connChannel->fd();
    char tmpstr[MAX_LINE];
    memset(tmpstr, 0, MAX_LINE);
    int readlength = ::read(sockfd, tmpstr, MAX_LINE);
    if (readlength < 0)
    {
        if (errno == ECONNRESET)
        {
            printf("Close socket fd for %d", sockfd);
            handleClose(sockfd);
        }
    } else if (readlength == 0)
    {
        printf("Read 0 from fd %d", sockfd);
        handleClose(sockfd);
    } else
    {
        string line(tmpstr, readlength);
        _inBuffer.append(line);
        //when receive the message, then call the callback directly
        _messageCallback(this, &_inBuffer);
    }
}

//when fd can be write, so should be shutdown when write complete
void TcpConnection::handleWrite()
{
    int sockfd = _connChannel->fd();
    if (_connChannel->isWritingCapable())
    {
        //buffer has data to write
        if (_outBuffer.readableBytes() > 0)
        {
            int writelength = ::write(sockfd, _outBuffer.peek(), _outBuffer.readableBytes());
            if (writelength > 0)
            {
                //remove the write data from buffer
                _outBuffer.retrieve(writelength);
                //if buffer is empty, close the write trigger
                if (_outBuffer.readableBytes() == 0)
                {
                    _connChannel->disableWriting();
                    //don't call the callback directly,coz callback will call send, when in loop thread
                    //it will call callback again when write complete, so put it in queue
                    //_completeCallback();
                    _loop->queueInLoop(std::bind(_completeCallback, this));
                }
            }
        }
    }
}

void TcpConnection::handleClose(int socketfd)
{
    _connChannel->disableReading();
    _connChannel->disableWriting();
    _closeCallback(socketfd);
}

//called by server when connection established, enable reading
//called by the main loop, one thread, so just call the callback function
void TcpConnection::connectEstablished()
{
    //enable the poller reading
    _connChannel->enableReading();
    //call the user callback functions
    _connCallback(this);
}

//called by server when responding to client
void TcpConnection::send(const string &msg)
{
    //while in loop thread,just send
    if (_loop->isInLoopThread())
    {
        sendInLoop(msg);
    } else
    {
        //void (TcpConnection::* fp)(const string &msg) =&TcpConnection::sendInLoop;
        _loop->queueInLoop(std::bind(&TcpConnection::sendInLoop, this, msg));
    }
}

void TcpConnection::sendInLoop(const string &msg)
{
    int writelen = 0;
    int sockfd = _connChannel->fd();
    //if buffer is empty, write directly
    if (_outBuffer.readableBytes() == 0)
    {
        writelen = ::write(sockfd, msg.c_str(), msg.size());
        //send completely
        if (writelen == msg.size())
        {
            _loop->queueInLoop(std::bind(_completeCallback, this));
            return;
        }
    }
    //after write, there is something left
    if (writelen >= 0 && writelen < msg.size())
    {
        _outBuffer.append(msg.substr(writelen, msg.size()));
        if (!_connChannel->isWritingCapable())
        {
            _connChannel->enableWriting();
        }
    }
}

void TcpConnection::setMessageCallback(MessageCallback msgCallback)
{
    _messageCallback = msgCallback;
}

void TcpConnection::setCompleteCallback(CompleteCallback completeCallback)
{
    _completeCallback = completeCallback;
}

void TcpConnection::setConnectionCallback(ConnectionCallback connCallback)
{
    _connCallback = connCallback;
}

void TcpConnection::setCloseCallback(CloseCallback closeCallback)
{
    _closeCallback = closeCallback;
}

//add functions
int TcpConnection::getSocketfd() {
    return _connChannel->fd();
}