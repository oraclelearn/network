//
// Created by chuli on 2019/2/12.
//

#ifndef NETWORK_NETWORKTYPE_H
#define NETWORK_NETWORKTYPE_H

//Channel List
typedef std::vector<Channel*> ChannelList;
typedef std::map<int, Channel*> ChannelMap;

//Epoll events
typedef std::vector<struct epoll_event> EpollEventList;

//callback definition
typedef std::function<void()> EventCallback;

#endif //NETWORK_NETWORKTYPE_H
