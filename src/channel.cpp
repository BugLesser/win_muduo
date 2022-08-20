#include "channel.h"
#include "event_loop.h"

Channel::Channel(EventLoop *loop, socket_type sockfd)
: loop_(loop)
, sockfd_(sockfd)
, events_(0)
, revents_(0) {
}

void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::handleEvent() {
    if((revents_ & kReadable) && readCallback_) {
        readCallback_();
    }
    if((revents_ & kWriteable) && writeCallback_) {
        writeCallback_();
    }
    if((revents_ & kClosed) && closeCallback_) {
        closeCallback_();
    }
    if((revents_ & kErrored) && errorCallback_) {
        errorCallback_();
    }
}
