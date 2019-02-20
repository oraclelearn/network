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
    void bindAddress(const uint16_t port);

    void listen();

    int accept();

    //for connections
    void close(int clientfd);

private:
    int _socketfd;
};

#endif //NETCONNECT_SOCKET_H
