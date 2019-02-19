//
// Created by chuli on 2019/2/11.
//

#ifndef NETCONNECT_SOCKET_H
#define NETCONNECT_SOCKET_H


class Socket {

    Socket();

    //getter
    int fd();

    //for acceptor
    void bindAddress(const string& IPAddress, const string& IPPort);
    void listen();
    int accept();

    //for connections
    void close();
private:
    int _socketfd;
};

#endif //NETCONNECT_SOCKET_H
