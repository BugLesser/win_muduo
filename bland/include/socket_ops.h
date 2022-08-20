#pragma once


#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#elif defined(__linux__)
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#endif

#ifdef _WIN32
using socket_type = SOCKET;
using socket_len_type = socklen_t;
using in_addr_type = SOCKADDR_IN;
using in6_addr_type = SOCKADDR_IN6;
using socket_addr_type = SOCKADDR;
const socket_type invalid_socket = INVALID_SOCKET;
const auto in_addr_any = INADDR_ANY;
const auto in6_addr_any = in6addr_any;
#elif defined(__linux__)
using socket_type = int;
using socket_len_type = socklen_t;
const socket_type invalid_socket = -1;
#endif

namespace socket_ops {

socket_type socket(int af, int type, int protocol);
int setNonblock(socket_type sockfd);
int bind(socket_type sockfd, const socket_addr_type* addr, int namelen);
int listen(socket_type sockfd, int backlog);
socket_type accept(socket_type sockfd, socket_addr_type *addr, int *addrlen);
int read(socket_type sockfd, char *buf, int len, int flags);
int write(socket_type sockfd, const char *buf, int len, int flags);
int shutdown(socket_type sockfd, int how);
int close(socket_type sockfd);


const socket_addr_type* sockaddr_cast(const in_addr_type* addr);
const socket_addr_type* sockaddr_cast(const in6_addr_type* addr);
socket_addr_type* sockaddr_cast(in_addr_type* addr);
socket_addr_type* sockaddr_cast(in6_addr_type* addr);

const in6_addr_type getLocalAddr(socket_type sockfd);
}
