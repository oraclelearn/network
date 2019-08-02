//
// Created by CHULI on 2019/6/13.
//

#ifndef NETWORK_CURRENTTHREAD_H
#define NETWORK_CURRENTTHREAD_H

namespace CurrentThread
{
    extern __thread int _cacheTid;
    void cacheTid();
    inline int tid()
    {
        if (_cacheTid == 0)
        {
            _cacheTid = 1;
        }
        return _cacheTid;
    }


}

#endif //NETWORK_CURRENTTHREAD_H
