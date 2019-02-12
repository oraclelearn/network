//
// Created by chuli on 2019/2/11.
//

#include "Acceptor.h"

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr)
        : _loop(loop),
          _acceptorSocket(socket::createNonblockingOrDie()),
          _acceptorChannel(loop, acceptorSocket_.fd()) {
    acceptorSocket_.bindAddress

}
