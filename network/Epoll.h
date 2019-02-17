//
// Created by chuli on 2019/2/12.
//
#include "Channel.h"
#include "NetworkType.h"
#include "EventLoop.h"

#ifndef NETWORK_EPOLL_H
#define NETWORK_EPOLL_H


class Epoll {
public:
    Epoll(EventLoop *loop);
    ~Epoll();

    //functions
    void poll(ChannelList& channelList);
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

private:
    //update channel
    void update(int operation, Channel* channel);

    int _epollfd;
    ChannelMap _channelsMap;

    //save the events of the poll
    const int  MAX_EVENTS = 500;
    struct epoll_event _events[MAX_EVENTS];

    EventLoop* _loop;


};


#endif //NETWORK_EPOLL_H
