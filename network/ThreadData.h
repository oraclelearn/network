//
// Created by CHULI on 2019/6/13.
//
#include "NetworkType.h"

#ifndef NETWORK_THREADDATA_H
#define NETWORK_THREADDATA_H

namespace CurrentThread
{
    struct ThreadData
    {
        ThreadFunc _func;
        string _name;

        ThreadData(ThreadFunc func, string name) :
                _func(func),
                _name(name)
        {

        }

        void runInThread()
        {
            CurrentThread::tid();
            try
            {
                //recall the function
                _func();
            } catch (Exception ex)
            {
                abort();
            }

        }
    };
}

#endif //NETWORK_THREADDATA_H
