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

private:
    Epoll* _epoller;
    bool _quit;

};


#endif //NETWORK_EVENTLOOP_H
