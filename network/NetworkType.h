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
typedef std::vector<EventCallback > EventCallbackList;
typedef std::fucntion<void(int)> NewConnection;
Typedef std::function<void(TcpConnection* conn, StringBuffer*)> MessageCallbak;

//TcpConnections
typedef  std::map<int fd, TcpConnection* conn> ConnectionMap;

static const int MAX_EVENTS = 500;
static const int MAX_LINE = 1024;

#endif //NETWORK_NETWORKTYPE_H
