//
// Created by chuli on 2019/2/12.
//

#ifndef NETWORK_EPOLL_H
#define NETWORK_EPOLL_H

#include "Channel.h"
#include "NetworkType.h"
#include <sys/epoll.h>

class EventLoop;

class  Epoller{
public:
    Epoller(EventLoop *loop);

    ~Epoller();

    //functions
    void poll(ChannelList &channelList);

    void updateChannel(Channel *channel);

    void removeChannel(Channel *channel);

private:
    //update channel
    void update(int operation, Channel *channel);

    int _epollfd;
    ChannelMap _channelsMap;

    //save the events of the poll
    struct epoll_event _events[MAX_EVENTS];

    EventLoop *_loop;


};


#endif //NETWORK_EPOLL_H
