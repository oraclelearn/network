# cmake_minimum_required(VERSION <specify CMake version here>)
project(netconnect)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

add_compile_options(-std=c++11)

add_executable(netconnect network/Acceptor.cpp network/Acceptor.h network/Channel.cpp network/Channel.h network/Socket.cpp network/Socket.h network/EventLoop.cpp network/EventLoop.h network/NetworkType.h network/Epoller.cpp network/Epoller.h network/TcpServer.cpp network/TcpServer.h network/TcpConnection.cpp network/TcpConnection.h network/StringBuffer.cpp network/StringBuffer.h network/EventLoopThread.cpp network/EventLoopThread.h network/Thread.cpp network/Thread.h network/MutexLock.h network/CurrentThread.h network/CurrentThread.cpp network/ThreadData.h network/ThreadPool.cpp network/ThreadPool.h network/MutexLockGuard.h network/Condition.h network/UnassignLockGuard.h network/EventLoopThreadPool.cpp network/EventLoopThreadPool.h network/MyServer.cpp network/MyServer.cpp network/MyServer.h network/main.cpp)

target_link_libraries(netconnect ${CMAKE_THREAD_LIBS_INIT})