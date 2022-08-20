#include "acceptor.h"

#include <cassert>

#include "event_loop.h"
#include "socket.h"
#include "inet_address.h"
#include "channel.h"

Acceptor::Acceptor(EventLoop* loop, const InetAddress& bindAddr)
: loop_(loop)
, listening_(false) {
    auto sockfd = socket_ops::socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != invalid_socket);
    socket_ops::setNonblock(sockfd);
    socket_ = new Socket(sockfd);
    socket_->bind(bindAddr);
    channel_ = new Channel(loop, sockfd);
    channel_->setReadCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor() {

}

void Acceptor::listen(int backlog) {
    listening_ = true;
    socket_->listen(backlog);
    channel_->enableReading();
}

void Acceptor::handleRead() {
    in_addr_type addr{};
    int addrLen = sizeof(in_addr_type);
    Socket *acceptSocket = socket_->accept((socket_addr_type*)&addr, &addrLen);

    if(newConnectionCallback_) {
        newConnectionCallback_(acceptSocket, InetAddress(addr));
    }
}
