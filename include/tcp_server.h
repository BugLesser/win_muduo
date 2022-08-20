#pragma once

#include "callbacks.h"

#include "inet_address.h"

class EventLoopThreadPool;
class Acceptor;
class EventLoop;

class TcpServer {
public:

    TcpServer(EventLoop* loop, const InetAddress& bindAddr);

    void setConnectionCallback(ConnectionCallback cb) { connectionCallback_ = std::move(cb); }
    void setMessageCallback(MessageCallback cb) { messageCallback_ = std::move(cb); }
    void setWriteCompleteCallback(WriteCompleteCallback cb) { writeCompleteCallback_ = std::move(cb); }
    void setCloseCallback(CloseCallback cb) { closeCallback_ = std::move(cb); }

    void setThreadNum(int threadNum);
    void start();
private:
    EventLoop* loop_;
    Acceptor* acceptor_;
    EventLoopThreadPool* threadPool_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    CloseCallback closeCallback_;

    void handleNewConnection(Socket *socket, const InetAddress& peerAddr);
    void threadFunc();
    EventLoop* getNextLoop();
};

