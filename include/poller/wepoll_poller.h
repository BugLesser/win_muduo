#pragma once

#include "poller.h"
#include "wepoll.h"


/* windows epoll poller */
class WEPollPoller : public Poller {
public:
    WEPollPoller(EventLoop *loop);
    void poll(std::vector<Channel*>& activeChannels, int timeout) override;
    void updateChannel(Channel *channel) override;
    void removeChannel(Channel *channel) override;
private:
    HANDLE epollfd_;
    std::vector<struct epoll_event> events_;
};
