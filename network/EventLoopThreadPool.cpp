//
// Created by CHULI on 2019/6/24.
//

#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *loop) : _baseLoop(loop),
                                                            _numThreads(0),
                                                            _next(0)
{

}

EventLoopThreadPool::~EventLoopThreadPool()
{

}

void EventLoopThreadPool::setNumThreads(int numThreads)
{
    _numThreads = numThreads;
}

void EventLoopThreadPool::start()
{
    for (int i = 0; i < _numThreads; ++i)
    {
        char id[32];
        snprintf(id, sizeof(id), "%d", i + 1);
        EventLoopThread *thread = new EventLoopThread(id);
        _threads.emplace_back(std::unique_ptr<EventLoopThread>(thread));
        _loops.emplace_back(thread->startLoop());
    }
}

EventLoop *EventLoopThreadPool::getNextEventLoop()
{
    EventLoop *loop = _baseLoop;
    if (_numThreads > 0)
    {
        loop = _loops[_numThreads];
    }
    ++_next;
    if(_next >= _numThreads)
        _next = 0;
    return loop;
}