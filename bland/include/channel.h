#pragma once

#include "socket_ops.h"

#include <functional>

#include "callbacks.h"

class EventLoop;

class Channel {
public:
    static const int kReadable = 1;
    static const int kWriteable = 2;
    static const int kClosed = 4;
    static const int kErrored = 8;

    Channel(EventLoop *loop, socket_type sockfd);
    ~Channel() = default;

    void enableReading() { events_ |= kReadable; update(); }
    void disableReading() { events_ &= ~kReadable; update(); }
    void enableWriting() { events_ |= kWriteable; update(); }
    void disableWriting() { events_ &= ~kWriteable; update(); }
    void enableClosing() { events_ |= kClosed; update(); }
    void disableClosing() { events_ &= ~kClosed; update(); }
    void enableErroring() { events_ |= kErrored; update(); }
    void disableErroring() { events_ &= ~kErrored; update(); }
    void disableAll() { events_ &= 0; update(); }

    void update();
    void handleEvent();
    void remove();

    inline socket_type sockfd() const noexcept { return sockfd_; }
    inline int events() const noexcept { return events_; }
    inline int revents() const noexcept { return revents_; }
    inline void setRevents(int revents) noexcept { revents_ = revents; }
    inline EventLoop* getLoop() noexcept { return loop_; }

    void setReadCallback(ChannelEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(ChannelEventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(ChannelEventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(ChannelEventCallback cb) { errorCallback_ = std::move(cb); }
private:
    EventLoop *loop_;
    socket_type sockfd_;
    int events_;
    int revents_;

    ChannelEventCallback readCallback_;
    ChannelEventCallback writeCallback_;
    ChannelEventCallback closeCallback_;
    ChannelEventCallback errorCallback_;
};
