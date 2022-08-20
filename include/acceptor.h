#pragma once

#include "socket.h"
#include "callbacks.h"

class EventLoop;
class Channel;

class Acceptor {
public:
    Acceptor(EventLoop* loop, const InetAddress& bindAddr);
    ~Acceptor();

    void setNewConnectionCallback(NewConnectionCallback cb) { newConnectionCallback_ = std::move(cb); }
    
    void listen(int backlog);
    bool listening() const { return listening_; }
private:
    EventLoop* loop_;
    Socket* socket_;
    Channel* channel_;
    NewConnectionCallback newConnectionCallback_;
    bool listening_;

    void handleRead();
};
