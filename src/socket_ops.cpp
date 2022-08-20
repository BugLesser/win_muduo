#include "socket_ops.h"


#ifdef _WIN32
struct __InitWSASocket_S {
    __InitWSASocket_S() {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
    ~__InitWSASocket_S() {
        WSACleanup();
    }
} __InitWSASocket;
#endif


socket_type socket_ops::socket(int af, int type, int protocol) {
    return ::socket(af, type, protocol);
}

int socket_ops::setNonblock(socket_type sockfd) {
    return 0;
}

int socket_ops::bind(socket_type sockfd, const socket_addr_type* addr, int namelen) {
    return ::bind(sockfd, addr, static_cast<socket_len_type>(sizeof(in6_addr_type)));
}

int socket_ops::listen(socket_type sockfd, int backlog) {
    return ::listen(sockfd, backlog);
}

socket_type socket_ops::accept(socket_type sockfd, socket_addr_type *addr, int *addrlen) {
    return ::accept(sockfd, addr, addrlen);
}

int socket_ops::read(socket_type sockfd, char *buf, int len, int flags) {
    return ::recv(sockfd, buf, len, flags);
}

int socket_ops::write(socket_type sockfd, const char *buf, int len, int flags) {
    return ::send(sockfd, buf, len, flags);
}

int socket_ops::shutdown(socket_type sockfd, int how) {
    return ::shutdown(sockfd, how);
}

int socket_ops::close(socket_type sockfd) {
    return ::closesocket(sockfd);
}

const socket_addr_type* socket_ops::sockaddr_cast(const in_addr_type* addr) {
    return static_cast<const socket_addr_type*>(static_cast<const void*>(addr));
}

const socket_addr_type* socket_ops::sockaddr_cast(const in6_addr_type* addr) {
    return static_cast<const socket_addr_type*>(static_cast<const void*>(addr));
}

socket_addr_type* socket_ops::sockaddr_cast(in_addr_type* addr) {
    return static_cast<socket_addr_type*>(static_cast<void*>(addr));
}

socket_addr_type* socket_ops::sockaddr_cast(in6_addr_type* addr) {
    return static_cast<socket_addr_type*>(static_cast<void*>(addr));
}
