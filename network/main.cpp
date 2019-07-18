//
// Created by CHULI on 2019/7/18.
//
#include "MyServer.h"
#include "EventLoop.h"

int main()
{
    printf("start the server");
    //main loop
    EventLoop loop;
    MyServer server(&loop, 11111);
    server.start(5);
    loop.loop();
}
