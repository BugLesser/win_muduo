#include "poller.h"
#include "poller/wepoll_poller.h"

Poller* Poller::newDefaultPoller(EventLoop* loop) {
    return new WEPollPoller(loop);
}
