#pragma once

#include <mutex>
#include <condition_variable>
#include <thread>

class EventLoop;

class EventLoopThread {
public:
    EventLoopThread() = default;
    ~EventLoopThread();
    EventLoop* startLoop();
private:
    EventLoop* loop_;
    std::thread* thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
    void threadFunc();
};