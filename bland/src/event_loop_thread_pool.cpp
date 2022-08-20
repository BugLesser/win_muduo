#include "event_loop_thread_pool.h"

#include "event_loop.h"
#include "event_loop_thread.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* loop)
: baseLoop_(loop)
, threadNum_(0)
, next_(0)
, started_(false) {
}

EventLoopThreadPool::~EventLoopThreadPool() {
    for(auto eventLoopThread : threads_) {
        delete eventLoopThread;
    }
}

void EventLoopThreadPool::start() {
    for(int i = 0; i < threadNum_; i++) {
        EventLoopThread* t = new EventLoopThread();
        threads_.push_back(t);
        loops_.push_back(t->startLoop());
    }
}

EventLoop* EventLoopThreadPool::getNextLoop() {
    EventLoop* loop = baseLoop_;

    if(!loops_.empty()) {
        loop = loops_[next_];
        ++next_;
        if(next_ >= loops_.size()) {
            next_ = 0;
        }
    }

    return loop;
}


void EventLoopThreadPool::threadFunc() {
}
