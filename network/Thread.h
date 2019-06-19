//
// Created by CHULI on 2019/5/24.
//

#ifndef NETWORK_THREAD_H
#define NETWORK_THREAD_H

#include <pthread.h>
#include "NetworkType.h"

class Thread : boost::noncopyable{
    Thread(ThreadFunc func, const string name);
    virtual ~Thread();

    //thread functions
    void start();
    void join();

    //getter
    bool isStarted(){ return  _started;};
    bool isJoined(){ return  _joined;};
    string& name(){return _name;};
    pthread_t pthreadId(){ return _pthreadId;}

private:
    bool _started;
    bool _joined;
    pthread_t _pthreadId;
    ThreadFunc _func;
    string _name;
};

#endif //NETWORK_THREAD_H
