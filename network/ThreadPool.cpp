//
// Created by CHULI on 2019/6/13.
//

#include "ThreadPool.h"
#include "Thread.cpp"
#include "MutexLock.h"

ThreadPool::ThreadPool(string poolName) : _name(poolName),
                                          _running(false),
                                          _maxNumTask(100),
                                          _mutex(),
                                          _notEmpty(_mutex),
                                          _notFull(_mutex)
{

}

virtual ThreadPool::~ThreadPool()
{
    if (_running)
        stop();
}

void ThreadPool::start(int numThreads)
{
    if (numThreads <= 0)
        return;

    _running = true;
    _threads.reserve(numThreads);

    for (int i = 0; i < numThreads; ++i)
    {
        char id[32];
        snprintf(id, sizeof(id), i + 1);
        _threads.emplace_back(new Thread(std::bind(&ThreadPool::runInThread, this), _name + id));
        _threads[i]->start();
    }
}

void ThreadPool::runInThread()
{
    while (_running)
    {
        ThreadFunc func = take();
        if (func)
        {
            func();
        }
    }
}

void ThreadPool::run(ThreadFunc task)
{
    //lock
    MutexLock lock(_mutex);
    //if queue is full
    while(_queue.size() >= _maxNumTask)
    {
        _notFull.wait();
    }

    _queue.push_back(std::move(task));  //push into queue
    _notEmpty.notify(); //notify the thread
    //unlock
}

ThreadFunc ThreadPool::take()
{
    //lock
    MutexLock lock(_mutex);
    //if queue is empty
    while(_queue.empty() && _running)
    {
        _notEmpty.wait();
    }

    ThreadFunc func = _queue.front();
    _queue.pop_front();
    _notFull.notify();

    return func;
    //unlock
}