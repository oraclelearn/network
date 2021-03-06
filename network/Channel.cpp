//
// Created by chuli on 2019/2/11.
//

#include "Channel.h"
#include <poll.h>

Channel::Channel(EventLoop *loop, int socketfd) :
        _loop(loop),
        _socketfd(socketfd),
        _set_events(0),
        _rec_events(0)
{

}

Channel::~Channel()
{
}

int Channel::fd()
{
    return _socketfd;
}

int Channel::get_setevents()
{
    return _set_events;
}

bool Channel::isWritingCapable()
{
    return _set_events & POLLOUT;
}

void Channel::set_recevents(int recevents)
{
    _rec_events = recevents;
}

void Channel::enableReading()
{
    _set_events |= (POLLIN | POLLPRI);
    _loop->updateChannel(this);
}

void Channel::enableWriting()
{
    _set_events |= POLLOUT;
    _loop->updateChannel(this);
}

void Channel::disableReading()
{
    _set_events &= ~(POLLIN | POLLPRI);
    _loop->updateChannel(this);
}

void Channel::disableWriting()
{
    _set_events &= ~POLLOUT;
    _loop->updateChannel(this);
}

void Channel::setReadCallback(EventCallback readCallback)
{
    _readCallback = std::move(readCallback);
}

void Channel::setWriteCallback(EventCallback writeCallback)
{
    _writeCallback = std::move(writeCallback);
}

void Channel::handleEvent()
{
    if (_rec_events & (POLLIN | POLLPRI | POLLRDHUP))
    {
        if (_readCallback)
            _readCallback();
    }

    if (_rec_events & POLLOUT)
    {
        if (_writeCallback)
            _writeCallback();
    }
}
