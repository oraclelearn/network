//
// Created by CHULI on 2019/6/13.
//

#ifndef NETWORK_CURRENTTHREAD_H
#define NETWORK_CURRENTTHREAD_H

#include <sys/syscall.h>

namespace CurrentThread
{
    extern __thread int _cacheTid;

    void cacheTid()
    {
        if(_cacheTid == 0)
        {
            _cacheTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }

    inline int tid()
    {
        if (_cacheTid == 0)
        {
            cacheTid();
        }
        return _cacheTid;
    }
}

#endif //NETWORK_CURRENTTHREAD_H
