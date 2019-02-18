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
        doPendingCallback();
    }
}

void EventLoop::updateChannel(Channel *channel) {
    _epoller->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel) {
    _epoller->removeChannel(channel);
}

void EventLoop::handleInLoop(EventCallback callback) {
    _pendingCallbacks.push_back(callback);
}

void EventLoop::doPendingCallback() {
    EventCallbackList list;
    _pendingCallbacks.swap(list);

    for( const EventCallback& callback : list){
        callback();
    }
}
