//
// Created by CHULI on 2019/6/13.
//

#ifndef NETWORK_THREADPOOL_H
#define NETWORK_THREADPOOL_H

#include "NetworkType.h"
#include "MutexLock.h"
#include "Thread.h"
#include "Condition.h"
#include <memory>
#include <deque>

class ThreadPool : boost::noncopyable
{
public:
    ThreadPool(string poolName);
    ~ThreadPool();

    //operations
    void start(int numThreads);
    void run(ThreadFunc task);
    void stop();

private:
    //inner functions
    void runInThread();
    ThreadFunc take();

    //consumer and thread
    std::vector<std::unique_ptr<Thread>> _threads; // threads
    std::deque<ThreadFunc > _queue;     //consumer tasks

    //threadpool status
    string _name;
    bool _running;
    unsigned int _maxNumTask;

    //thread condition variables
    mutable MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
};


#endif //NETWORK_THREADPOOL_H
