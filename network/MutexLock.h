//
// Created by CHULI on 2019/6/12.
//

#ifndef NETWORK_MUTEXLOCK_H
#define NETWORK_MUTEXLOCK_H

class MutexLock : boost::noncopyable
{
public:
    MutexLock():holder_(0)
    {
        MCHECK(pthread_mutex_init(&mutex_, NULL));
    }
    ~MutexLock()
    {
        assert(holder_ == 0);
        MCHECK(pthread_mutex_destroy(&mutex_));
    }
    bool isLocketByThisThread() const
    {
        return holder_ == CurrentThread::tid();
    }
    void assertLocked() const
    {
        assert(isLocketByThisThread());
    }
    void lock()
    {
        MCHECK(pthread_mutex_lock(&mutex_));
        assignHolder();
    }
    void unlock()
    {
        unassignHolder();
        MCHECK(pthread_mutex_unlock(&mutex_));
    }
    pthread_mutex_t* getPthreadMutex() /* non-const */　　　
    {
        return &mutex_;
    }
private:
    void unassignHolder()
    {
        holder_ = 0;
    }
    void assignHolder()
    {
        holder_ = CurrentThread::tid();
    }
private:
    pthread_mutex_t  mutex_;
    pid_t holder_;       // 如果不是同一个线程的加锁和解锁则会失败
};

#endif //NETWORK_MUTEXLOCK_H
