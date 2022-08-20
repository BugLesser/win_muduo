#include "poller.h"
#include "channel.h"


Poller::Poller(EventLoop *loop)
: loop_(loop) {
}

Channel *Poller::findChannel(socket_type sockfd) {
    if(channels_.find(sockfd) != channels_.end()) {
        return channels_[sockfd];
    }
    return nullptr;
}

bool Poller::hasChannel(Channel *channel) {
    auto it = channels_.find(channel->sockfd());
    return it != channels_.end() && it->second == channel;
}
