# cmake_minimum_required(VERSION <specify CMake version here>)
project(netconnect)

set(CMAKE_CXX_STANDARD 11)

add_executable(netconnect main.cpp network/Acceptor.cpp network/Acceptor.h network/Channel.cpp network/Channel.h network/Socket.cpp network/Socket.h network/EventLoop.cpp network/EventLoop.h network/NetworkType.h network/Epoll.cpp network/Epoll.h network/TcpServer.cpp network/TcpServer.h network/TcpConnection.cpp network/TcpConnection.h)