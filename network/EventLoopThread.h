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

    string _name;
    EventLoop* _loop;
    MutexLock _mutex;
    Condition _cond;
    Thread _thread;

};


#endif //NETWORK_EVENTLOOPTHREAD_H
