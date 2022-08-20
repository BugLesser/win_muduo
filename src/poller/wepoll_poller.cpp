#include "poller/wepoll_poller.h"

#include <cassert>

#include "channel.h"

WEPollPoller::WEPollPoller(EventLoop *loop)
: Poller(loop)
, events_(8) {
    epollfd_ = epoll_create1(0);
    assert(epollfd_ != nullptr);
}

void WEPollPoller::poll(std::vector<Channel*>& activeChannels, int timeout) {
    int nfds = epoll_wait(epollfd_, &*events_.begin(), events_.size(), timeout);
    assert(nfds >= 0);
    for(int i = 0; i < nfds; i++) {
        auto event = events_[i];
        auto channel = static_cast<Channel*>(event.data.ptr);
        int revents = 0;
        if(event.events & (EPOLLIN | EPOLLPRI)) {
            revents |= Channel::kReadable;
        }
        if(event.events & (EPOLLOUT)) {
            revents |= Channel::kWriteable;
        }
        if(event.events & (EPOLLRDHUP)) {
            revents |= Channel::kClosed;
        }
        if(event.events & (EPOLLERR)) {
            revents |= Channel::kErrored;
        }
        channel->setRevents(revents);
        activeChannels.push_back(channel);
    }
    if(static_cast<size_t>(nfds) >= events_.size()) {
        events_.resize(events_.size() * 1.5);
    }
}

void WEPollPoller::updateChannel(Channel *channel) {
    assert(channel != nullptr);
    epoll_event event{};
    int events = 0;
    if(channel->events() & Channel::kReadable) {
        events |= (EPOLLIN | EPOLLPRI);
    }
    if(channel->events() & Channel::kWriteable) {
        events |= EPOLLOUT;
    }
    if(channel->events() & Channel::kClosed) {
        events |= EPOLLRDHUP;
    }
    if(channel->events() & Channel::kErrored) {
        events |= EPOLLERR;
    }
    event.events = events;
    event.data.ptr = static_cast<void*>(channel);
    if(hasChannel(channel)) {
        epoll_ctl(epollfd_, EPOLL_CTL_MOD, channel->sockfd(), &event);
    } else {
        channels_[channel->sockfd()] = channel;
        epoll_ctl(epollfd_, EPOLL_CTL_ADD, channel->sockfd(), &event);
    }
}

void WEPollPoller::removeChannel(Channel *channel) {
    assert(channel != nullptr);
    assert(hasChannel(channel));
    channels_.erase(channel->sockfd());
    epoll_ctl(epollfd_, EPOLL_CTL_DEL, channel->sockfd(), nullptr);
}
