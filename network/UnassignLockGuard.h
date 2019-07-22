//
// Created by CHULI on 2019/6/20.
//

#ifndef NETWORK_UNASSIGNLOCKGUARD_H
#define NETWORK_UNASSIGNLOCKGUARD_H

#include "MutexLock.h"

class UnassignLockGurad
{
public:
    UnassignLockGurad(MutexLock& mutex): _mutex(mutex)
    {
        _mutex.unassignHolder();
    }

    ~UnassignLockGurad()
    {
        _mutex.assignHolder();
    }
private:
    MutexLock& _mutex;
};

#endif //NETWORK_UNASSIGNLOCKGUARD_H
