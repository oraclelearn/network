//
// Created by CHULI on 2019/6/20.
//

#ifndef NETWORK_CONDITION_H
#define NETWORK_CONDITION_H

#include "MutexLock.h"
#include "UnassignLockGuard.h"

class Condition
{
public:
    Condition(MutexLock& mutex):_mutex(mutex)
    {
        pthread_cond_init(&_cond, NULL);
    }

    ~Condition()
    {
        pthread_cond_destroy(&_cond);
    }

    void wait()
    {
        UnassignLockGurad ug(_mutex);
        pthread_cond_wait(&_cond, _mutex.getPthreadMutex());
    }

    void notify()
    {
        pthread_cond_signal(&_cond);
    }

    void notifyAll()
    {
        pthread_cond_broadcast(&_cond);
    }

private:
    MutexLock& _mutex;
    pthread_cond_t _cond;
};

#endif //NETWORK_CONDITION_H
