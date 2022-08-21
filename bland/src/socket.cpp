#include "socket.h"

#include <cassert>

Socket::Socket(socket_type sockfd)
: sockfd_(sockfd) {}


Socket::Socket(Socket &&socket) noexcept {
    this->sockfd_ = socket.sockfd_;
    socket.sockfd_ = invalid_socket;
}

Socket::~Socket() {
    // TODO check close
}

socket_type Socket::sockfd() {
    return sockfd_;
}

Socket &Socket::operator=(Socket &&other) noexcept {
    assert(this != &other);
    this->sockfd_ = other.sockfd_;
    other.sockfd_ = invalid_socket;
    return *this;
}

void Socket::swap(Socket &other) {
    socket_type tmp = other.sockfd_;
    other.sockfd_ = this->sockfd_;
    this->sockfd_ = tmp;
}

void Socket::bind(const InetAddress &address) {
    socket_ops::bind(sockfd_, address.sockAddr(), 0);
}

void Socket::listen(int backlog) {
    assert(::listen(sockfd_, backlog) == 0);
}

Socket* Socket::accept(socket_addr_type *addr, int *addrlen) {
    auto sock = socket_ops::accept(sockfd_, addr, addrlen);
    assert(sock != invalid_socket);
    return new Socket(sock);
}

int Socket::write(const char* buf, int len) {
    return socket_ops::write(sockfd_, buf, len, 0);
}

void Socket::close() {
    socket_ops::close(sockfd_);
}
