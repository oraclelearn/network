//
// Created by CHULI on 2019/6/13.
//

#ifndef NETWORK_THREADPOOL_H
#define NETWORK_THREADPOOL_H

#include "NetworkType.h"


class ThreadPool : boost::noncopyable
{
public:
    ThreadPool();
    virtual ~ThreadPool();

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
    bool _running;
    string _name;
    int _maxNumTask;

    //thread condition variables
    mutable MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
};


#endif //NETWORK_THREADPOOL_H
