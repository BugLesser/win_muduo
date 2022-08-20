#include "event_loop_thread.h"

#include "event_loop.h"

#include <functional>

EventLoop* EventLoopThread::startLoop() {
    thread_ = new std::thread(std::bind(&EventLoopThread::threadFunc, this));
    
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this](){
        return this->loop_ != nullptr;
    });

    return loop_;
}

EventLoopThread::~EventLoopThread() {
    if(thread_) {
        if(thread_->joinable()) thread_->detach();
        delete thread_;
    }
}

void EventLoopThread::threadFunc() {
    EventLoop loop;
    loop_ = &loop;
    cond_.notify_all();
    loop.run();
}
