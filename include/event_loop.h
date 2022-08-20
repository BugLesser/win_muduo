#pragma once

#include <vector>

class Channel;
class Poller;

class EventLoop {
public:
    EventLoop();
    void run();
    void quit() { quit_ = true; }
    void updateChannel(Channel *channel);
private:
    Poller *poller_;
    bool quit_;
    std::vector<Channel*> activeChannels_;
};
