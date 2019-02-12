//
// Created by chuli on 2019/2/12.
//

#include "EventLoop.h"

EventLoop::EventLoop() :
        _epoller(new Epoll()),
        _quit(false) {

}

EventLoop::~EventLoop() {
    _epoller = NULL;
}

void EventLoop::loop() {
    while (!_quit) {
        ChannelList activeChannels;
        _epoller.poll(&activeChannels);
        for (Channel *channel : activeChannels) {
            channel->handleEvent();
        }
    }
}

