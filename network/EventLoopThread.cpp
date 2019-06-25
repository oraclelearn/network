//
// Created by CHULI on 2019/5/24.
//

#include "EventLoopThread.h"
#include "MutexLockGuard.h"

EventLoopThread::EventLoopThread() : _loop(NULL),
                                     _mutex(),
                                     _cond(_mutex),
                                     _thread(std::bind(&EventLoopThread::threadFunc, this), name)
{
}

EventLoopThread::~EventLoopThread()
{
    if(_loop != NULL)
    {
        _loop->quit();
        _thread.join();
    }
}

EventLoop* EventLoopThread::startLoop()
{
    _thread.start();

    EventLoop* loop = NULL;
    {
        MutexLockGuard lock(_mutex);
        while(_loop == NULL)
        {
            _cond.wait();
        }
        loop = _loop;
    }
    return loop;
}

void EventLoopThread::threadFunc()
{
    EventLoop loop;
    {
        MutexLockGuard lock(_mutex);
        _loop = &loop;
        _cond.notify();
    }
    _loop->loop();

    //when exit
    MutexLockGuard lock(_mutex);
    _loop = NULL;
}