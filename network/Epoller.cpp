//
// Created by chuli on 2019/2/12.
//

#include "Epoller.h"
#include <unistd.h>
#include <string.h>

Epoller::Epoller(EventLoop *loop)
        : _loop(loop),
          _epollfd(::epoll_create(1))
{ //create epollfd
    if (_epollfd < 0)
    {
        printf("Epoller::Epoller error\n");
    }
}

Epoller::~Epoller()
{
    //close the epollfd
    ::close(_epollfd);
}

void Epoller::poll(ChannelList &channelList)
{
    int fds = ::epoll_wait(_epollfd, _events, MAX_EVENTS, -1);
    if (fds < 0)
    {
        printf("Epoller::poll error\n");
        return;
    }
    for (int i = 0; i < fds; i++)
    {
        Channel *channel = static_cast<Channel *>(_events[i].data.ptr);
        channel->set_recevents(_events[i].events);
        channelList.push_back(channel);
    }
}

void Epoller::updateChannel(Channel *channel)
{
    int fd = channel->fd();
    //not find in map, add
    if (_channelsMap.find(fd) == _channelsMap.end())
    {
        _channelsMap[fd] = channel;
        update(EPOLL_CTL_ADD, channel);
    }
        //find in map, modify
    else
    {
        _channelsMap[fd] = channel;
        update(EPOLL_CTL_MOD, channel);
    }
}

void Epoller::removeChannel(Channel *channel)
{
    int fd = channel->fd();
    //not find in map, return
    if (_channelsMap.find(fd) == _channelsMap.end())
    {
        return;
    }
        //find in map, delete
    else
    {
        _channelsMap.erase(fd);
        update(EPOLL_CTL_DEL, channel);
    }
}

void Epoller::update(int operation, Channel *channel)
{
    //initialize the event
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = channel->get_setevents();
    event.data.ptr = channel;
    int fd = channel->fd();

    //add event to epoll
    if (::epoll_ctl(_epollfd, operation, fd, &event) < 0)
    {
        printf("Epoller::update error\n");
    }
}