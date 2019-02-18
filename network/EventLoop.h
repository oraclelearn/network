//
// Created by chuli on 2019/2/12.
//

#include "NetworkType.h"

#ifndef NETWORK_EVENTLOOP_H
#define NETWORK_EVENTLOOP_H


class EventLoop {
public:
    EventLoop();
    ~EventLoop();

    //functions
    void loop();
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    void handleInLoop(EventCallback callback);

private:
    Epoll* _epoller;
    bool _quit;

    EventCallbackList _pendingCallbacks;

    //functions
    void doPendingCallback();
};


#endif //NETWORK_EVENTLOOP_H
