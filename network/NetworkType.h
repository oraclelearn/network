//
// Created by chuli on 2019/2/12.
//

#ifndef NETWORK_NETWORKTYPE_H
#define NETWORK_NETWORKTYPE_H

#include <vector>
#include <map>
#include <functional>

class TcpConnection;
class Channel;
class StringBuffer;

//Channel List
typedef std::vector<Channel*> ChannelList;
typedef std::map<int, Channel*> ChannelMap;

//Epoll events
typedef std::vector<struct epoll_event> EpollEventList;

//callback definition
typedef std::function<void()> EventCallback;
typedef std::vector<EventCallback > EventCallbackList;
typedef std::function<void(int)> NewConnection;
typedef std::function<void(TcpConnection*, StringBuffer*)> MessageCallback;
typedef std::function<void(TcpConnection*)> CompleteCallback;
typedef std::function<void(TcpConnection*)> ConnectionCallback;
typedef std::function<void(TcpConnection*)> CloseCallback;

//TcpConnections
typedef  std::map<int, TcpConnection*> ConnectionMap;
typedef  std::map<int, TcpConnection*>::iterator ConnectionMapIter;

static const int MAX_EVENTS = 500;
static const int MAX_LINE = 65536;

//Thread
typedef std::function<void()> ThreadFunc;

#endif //NETWORK_NETWORKTYPE_H
