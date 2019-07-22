//
// Created by chuli on 2019/2/12.
//

#include "EventLoop.h"
#include "Epoller.h"
#include <sys/eventfd.h>

EventLoop::EventLoop() :
        _epoller(new Epoller(this)),
        _quit(false),
        _wakeupFd(createWakeupFd()),
        _wakeupChannel(new Channel(this, _wakeupFd))
{

}

EventLoop::~EventLoop()
{
    _epoller = NULL;
}

int EventLoop::createWakeupFd()
{
    int eventFd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (eventFd < 0)
    {
        printf("EventLoop::createWakeupFd error");
    }
    return eventFd;
}

void EventLoop::loop()
{
    while (!_quit)
    {
        ChannelList activeChannels;
        _epoller->poll(activeChannels);
        for (Channel *channel : activeChannels)
        {
            channel->handleEvent();
        }
        doPendingCallback();
    }
}

void EventLoop::updateChannel(Channel *channel)
{
    _epoller->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel)
{
    _epoller->removeChannel(channel);
}

void EventLoop::handleInLoop(EventCallback callback)
{
    _pendingCallbacks.push_back(callback);
}

void EventLoop::doPendingCallback()
{
    EventCallbackList list;
    _pendingCallbacks.swap(list);

    for (const EventCallback &callback : list)
    {
        callback();
    }
}

bool EventLoop::isInLoopThread()
{
    return true;
}

void EventLoop::runInLoop(EventCallback ecb)
{
    if (isInLoopThread())
    {
        ecb();
    } else
    {
        queueInLoop(ecb);
    }
}

void EventLoop::queueInLoop(EventCallback ecb)
{
    _pendingCallbacks.push_back(ecb);

}

void EventLoop::quit() {
    _quit = true;
}