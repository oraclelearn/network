//
// Created by chuli on 2019/2/12.
//

#include "Epoll.h"

Epoll::Epoll()
        //create epollfd
        : _epollfd(::epoll_create(1)){
    if (_epollfd < 0) {
        printf("Epoll::Epoll error");
    }
}

Epoll::~Epoll() {
    //close the epollfd
    ::close(_epollfd);
}

void Epoll::poll(ChannelList &channelList) {
    int fds = ::epoll_wait(_epollfd, _events, MAX_EVENTS, -1);
    if (fds < 0) {
        printf("Epoll::poll error");
        return;
    }
    for(int i = 0; i < fds; i ++){
        Channel* channel = static_cast<Channel*>_events[i].data.ptr;
        channel->setRevents(_events[i].events);
        channelList.push_back(channel);
    }
}

void Epoll::updateChannel(Channel *channel) {
    int fd = channel->fd();
    //not find in map, add
    if(_channelsMap.find(fd) == _channelsMap.end()){
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

void Epoll::removeChannel(Channel *channel) {
    int fd = channel->fd();
    //not find in map, return
    if(_channelsMap.find(fd) == _channelsMap.end()){
        return;
    }
    //find in map, delete
    else
    {
        _channelsMap.erase(fd);
        update(EPOLL_CTL_DEL, channel);
    }
}

void Epoll::update(int operation, Channel *channel) {
    struct epoll_event event;
    memset(&event,0, sizeof(event));
    event.envents = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();

    if((::epoll_ctl(epollfd_, operation, fd, &event) < 0){
        printf("Epoll::update error");
    }
}