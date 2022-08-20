#pragma once

#include "socket_ops.h"
#include "inet_address.h"


class Socket {
public:
    explicit Socket(socket_type sockfd);
    Socket(Socket&& socket) noexcept;
    ~Socket();
    socket_type sockfd();
    Socket& operator=(Socket &&other) noexcept;
    void swap(Socket &other);
    void bind(const InetAddress& address);
    void listen(int backlog);
    Socket* accept(socket_addr_type *addr, int *addrlen);
    int read(char* buf, int len);
    int write(const char* buf, int len);
    void close();
private:
    socket_type sockfd_;
};
