//
// Created by CHULI on 2019/5/24.
//

#include "Thread.h"
#include "CurrentThread.h"
#include "ThreadData.h"

void *startThread(void *obj)
{
    CurrentThread::ThreadData *data = static_cast<CurrentThread::ThreadData *  >(obj);
    data->runInThread();
    return  NULL;
}

Thread::Thread(ThreadFunc func, const string name)
        : _started(false),
          _joined(false),
          _pthreadId(0),
          _func(std::move(func)),
          _name(name)
{
}

Thread::~Thread()
{
    //if thread is started and no joined
    if (_started && !_joined)
    {
        pthread_detach(_pthreadId);
    }
}

void Thread::start()
{
    //create threaddata for this thread
    CurrentThread::ThreadData *data = new CurrentThread::ThreadData(_func, _name);
    //call the pthread_create
    if (pthread_create(&_pthreadId, NULL, &startThread, data))
    {
        printf("pthread_create failed\n");
        delete data;
    } else
    {
        _started = true;
    }
}

void Thread::join()
{
    //thread join
    if (pthread_join(_pthreadId, NULL))
    {
        printf("pthread_join failed\n");
    } else
    {
        _joined = true;
    }
}