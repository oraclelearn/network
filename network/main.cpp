//
// Created by CHULI on 2019/7/18.
//
#include "MyServer.h"
#include "EventLoop.h"
#include <pthread.h>

int main()
{
    printf("start the server");
    //main loop
    EventLoop loop;
    MyServer server(&loop, 11111);
    server.start(5);
    loop.loop();
}
/*

void* worker1(void* arg){
    int tid = CurrentThread::tid();
    printf("The worker1's tid is %d\n", tid);
    return NULL;
}

void* worker2(void* arg){
    int tid = CurrentThread::tid();
    printf("The worker2's tid is %d\n", tid);
    return NULL;
}

int main()
{
    int tid = CurrentThread::tid();

    pthread_t pid1,pid2;
    pthread_create(&pid1,NULL,worker1,NULL);
    pthread_create(&pid2,NULL,worker2,NULL);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);

    printf("The main's tid is %d\n", tid);

    return  1;
}
*/

