#include "event_loop.h"
#include "poller.h"
#include "channel.h"

#include <cassert>

EventLoop::EventLoop()
: poller_(Poller::newDefaultPoller(this))
, quit_(false) {
}

void EventLoop::updateChannel(Channel *channel) {
    assert(channel->getLoop() == this);    
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel) {
    assert(channel->getLoop() == this);    
    poller_->removeChannel(channel);
}

void EventLoop::run() {
    while(!quit_) {
        activeChannels_.clear();
        poller_->poll(activeChannels_, -1);
        for(auto& activeChannel : activeChannels_) {
            activeChannel->handleEvent();
        }
    }
}

