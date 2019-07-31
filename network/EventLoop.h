//
// Created by chuli on 2019/2/12.
//
#ifndef NETWORK_EVENTLOOP_H
#define NETWORK_EVENTLOOP_H

#include "NetworkType.h"
#include "Channel.h"

class Epoller;

class EventLoop
{
public:
    EventLoop();

    ~EventLoop();

    //functions
    void loop();

    void updateChannel(Channel *channel);

    void removeChannel(Channel *channel);

    void handleInLoop(EventCallback callback);

    bool isInLoopThread();

    void runInLoop(EventCallback ecb);

    void queueInLoop(EventCallback ecb);

    void wakeup();

    void quit();

private:
    //functions
    int createWakeupFd();

    void doPendingCallback();

    //members
    Epoller *_epoller;
    bool _quit;
    int _wakeupFd;
    Channel *_wakeupChannel;

    EventCallbackList _pendingCallbacks;

};


#endif //NETWORK_EVENTLOOP_H
