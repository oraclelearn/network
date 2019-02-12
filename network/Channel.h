//
// Created by chuli on 2019/2/11.
//

#ifndef NETCONNECT_CHANNEL_H
#define NETCONNECT_CHANNEL_H


class Channel {
public:
    Channel(Eventloop *loop, int socketfd);

    //functions
    void enableReading();
    void enableWriting();
    void disableReading();
    void disableWriting();

    //getter
    int fd();
    int events();
    int revents();

private:
    //loop and file discriptor
    int _socketfd;
    EventLoop* _loop;

    //event setter
    int _events;
    int _revents;

    //callback function
    EventCallback _readCallback;
    EventCallback  _writeCallback;

};


#endif //NETCONNECT_CHANNEL_H
