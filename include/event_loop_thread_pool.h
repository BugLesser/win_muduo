#pragma once

#include <vector>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool {
public:
    EventLoopThreadPool(EventLoop* loop);
    ~EventLoopThreadPool();
    
    void setThreadNum(int threadNum) { threadNum_ = threadNum; }

    void start();

    EventLoop* getNextLoop();
private:
    EventLoop* baseLoop_;
    int threadNum_;
    std::size_t next_;
    bool started_;
    std::vector<EventLoopThread*> threads_;
    std::vector<EventLoop*> loops_;

    void threadFunc();
};

