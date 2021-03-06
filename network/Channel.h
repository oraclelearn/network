//
// Created by chuli on 2019/2/11.
//

#ifndef NETCONNECT_CHANNEL_H
#define NETCONNECT_CHANNEL_H

#include "NetworkType.h"
#include "EventLoop.h"
class EventLoop;

class Channel {
public:
    Channel(EventLoop* loop, int socketfd);

    ~Channel();

    //functions
    void enableReading();

    void enableWriting();

    void disableReading();

    void disableWriting();

    bool isWritingCapable();

    //getter and setter
    int fd();

    int get_setevents();

    void set_recevents(int recevents);

    //set the callback functions
    void handleEvent();

    void setReadCallback(EventCallback readCallback);

    void setWriteCallback(EventCallback writeCallback);

private:
    //loop and file discriptor
    EventLoop *_loop;
    int _socketfd;

    //events
    int _set_events;    //the events that been set
    int _rec_events;   //the events that been received from epoll

    //callback function
    EventCallback _readCallback;
    EventCallback _writeCallback;
};


#endif //NETCONNECT_CHANNEL_H
