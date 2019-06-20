//
// Created by CHULI on 2019/6/19.
//

#ifndef NETWORK_MUTEXLOCKGUARD_H
#define NETWORK_MUTEXLOCKGUARD_H

#include "MutexLock.h"

class MutexLockGuard : boost::noncopyable   //RAII Locker
{
public:
    MutexLockGuard(MutexLock mutex) : _mutex(_mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        _mutex.unlock();
    }

private:
    MutexLock _mutex;
};

#endif //NETWORK_MUTEXLOCKGUARD_H
