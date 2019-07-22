//
// Created by CHULI on 2019/5/24.
//

#ifndef NETWORK_EVENTLOOPTHREAD_H
#define NETWORK_EVENTLOOPTHREAD_H

#include "EventLoop.h"
#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include <memory>


class EventLoopThread {

public:
    EventLoopThread(const string name);
    virtual ~EventLoopThread();

    EventLoop* startLoop();

private:
    void threadFunc();

    EventLoop* _loop;
    Thread _thread;

    MutexLock _mutex;
    Condition _cond;

    string _name;

};


#endif //NETWORK_EVENTLOOPTHREAD_H
