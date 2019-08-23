//
// Created by chuli on 2019/2/12.
//

#include "EventLoop.h"
#include "Epoller.h"
#include "MutexLockGuard.h"
#include "CurrentThread.h"
#include <sys/eventfd.h>

EventLoop::EventLoop() :
        _epoller(new Epoller(this)),
        _quit(false),
        _wakeupFd(createWakeupFd()),
        _wakeupChannel(new Channel(this, _wakeupFd)),
        _threadId(CurrentThread::tid())
{
    _wakeupChannel->setReadCallback(std::bind(&EventLoop::handleRead, this));
    _wakeupChannel->enableReading();
}



EventLoop::~EventLoop()
{
    _wakeupChannel->disableReading();
    ::close(_wakeupFd);
    delete _epoller;
    _epoller = NULL;
}

int EventLoop::createWakeupFd()
{
    int eventFd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (eventFd < 0)
    {
        printf("EventLoop::createWakeupFd error\n");
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


bool EventLoop::isInLoopThread()
{
    return _threadId == CurrentThread::tid();
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
    MutexLockGuard lock(_mutex);
    _pendingCallbacks.push_back(ecb);
    if(!isInLoopThread() || _pendingCallbacks.size() > 0)
    {
        wakeup();
    }
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = ::read(_wakeupFd, &one, sizeof(one));
    if (n != sizeof(one))
    {
        printf("EventLoop::handleRead() reads %zu bytes instead of 4\n", n);
    }
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = ::write(_wakeupFd, &one, sizeof(one));
    if(n != sizeof(one))
    {
        printf("EventLoop::wakeup() writes %zu bytes instead of 4\n", n);
    }
}

void EventLoop::doPendingCallback()
{
    EventCallbackList list;
    {
        MutexLockGuard lock(_mutex);
        _pendingCallbacks.swap(list);
    }

    for (const EventCallback &callback : list)
    {
        callback();
    }
}


void EventLoop::quit()
{
    _quit = true;
}