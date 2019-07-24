//
// Created by CHULI on 2019/6/13.
//
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <unistd.h>

namespace CurrentThread
{
    __thread int _cacheTid = 0;

    void cacheTid()
    {
        if (_cacheTid == 0)
        {
            _cacheTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }


}