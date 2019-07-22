//
// Created by CHULI on 2019/6/24.
//

#ifndef NETWORK_EVENTLOOPTHREADPOOL_H
#define NETWORK_EVENTLOOPTHREADPOOL_H

#include "EventLoop.h"
#include <memory>


class EventLoopThreadPool
{
public:
    EventLoopThreadPool(EventLoop* loop);
    ~EventLoopThreadPool();

    void setNumThreads(int numThreads);
    void start();

    EventLoop * getNextEventLoop();

private:
    //base loop
    EventLoop * _baseLoop;

    //threads
    int _numThreads;
    std::vector<std::unique_ptr<EventLoopThread>> _threads;
    std::vector<EventLoop *> _loops;

    //current loop index
    int _next;
};


#endif //NETWORK_EVENTLOOPTHREADPOOL_H
