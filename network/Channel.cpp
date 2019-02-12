//
// Created by chuli on 2019/2/11.
//

#include "Channel.h"
#include <poll.h>

Channel::Channel(Eventloop *loop, int socketfd) :
        _loop(loop),
        _socketfd(socketfd),
        _events(0),
        _revents(0) {

}

int Channel::fd() {
    return _socketfd;
}

int Channel::events() {
    return _events;
}

int Channel::revents() {
    return _revents;
}

void Channel::enableReading() {
    _events |= (POLLIN | POLLPRI);
    _loop->updateChannel();
}

void Channel::enableWriting() {
    _events |= POLLOUT;
    _loop->updateChannel();
}

void Channel::disableReading() {
    _evnets &= ~(POLLIN | POLLPRI);
    _loop->updateChannel();
}

void Channel::disableWriting() {
    _events &= ~POLLOUT;
    _loop->updateChannel();
}


