//
// Created by CHULI on 2019/6/12.
//

#ifndef NETWORK_MUTEXLOCK_H
#define NETWORK_MUTEXLOCK_H

#include <assert.h>
#include "CurrentThread.h"
#include<boost/noncopyable.hpp>

class MutexLock
{
public:
    MutexLock() : _holder(0)
    {
        pthread_mutex_init(&_mutex, NULL);
    }

    ~MutexLock()
    {
        assert(_holder == 0);
        pthread_mutex_destroy(&_mutex);
    }

    bool isLocketByThisThread() const
    {
        return _holder == CurrentThread::tid();
    }

    void assertLocked() const
    {
        assert(isLocketByThisThread());
    }

    void lock()
    {
        pthread_mutex_lock(&_mutex);
        assignHolder();
    }

    void unlock()
    {
        unassignHolder();
        pthread_mutex_unlock(&_mutex);
    }

    pthread_mutex_t *getPthreadMutex() /* non-const */
    {
        return &_mutex;
    }

    void assignHolder()
    {
        _holder = CurrentThread::tid();
    }

    void unassignHolder()
    {
        _holder = 0;
    }

private:
    pthread_mutex_t _mutex;
    pid_t _holder;       // 如果不是同一个线程的加锁和解锁则会失败
};

#endif //NETWORK_MUTEXLOCK_H
