#pragma once

#include <vector>
#include <map>

#include "socket_ops.h"

class Channel;
class EventLoop;

class Poller {
public:
    explicit Poller(EventLoop *loop);

    virtual void poll(std::vector<Channel*>& activeChannels, int timeout = -1) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    Channel* findChannel(socket_type sockfd);
    bool hasChannel(Channel *channel);

    static Poller* newDefaultPoller(EventLoop* loop);
protected:
    EventLoop *loop_;
    std::map<socket_type, Channel*> channels_;
};
