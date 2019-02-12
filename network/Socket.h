//
// Created by chuli on 2019/2/11.
//

#ifndef NETCONNECT_SOCKET_H
#define NETCONNECT_SOCKET_H


class Socket {

    Socket();

    int fd();

    void bindAddress(const string& IPAddress, const string& IPPort);
    void listen();

private:
    int _socketfd;
};

#endif //NETCONNECT_SOCKET_H
