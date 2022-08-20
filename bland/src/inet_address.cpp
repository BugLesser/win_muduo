#include "inet_address.h"

InetAddress::InetAddress(const std::string& ip, uint16_t port, bool ipv6)
: ipv6_(ipv6) {
    if(!ipv6) {
        ::memset(&addr_, 0, sizeof(addr_));
        addr_.sin_family = AF_INET;
        addr_.sin_addr.s_addr = ::inet_addr(ip.c_str());
        addr_.sin_port = ::htons(port);
    } else {
    }
}

const socket_addr_type* InetAddress::sockAddr() const noexcept {
    return socket_ops::sockaddr_cast(&addr6_);
}

std::string InetAddress::toIp() const {
    return std::string(::inet_ntoa(addr_.sin_addr));
}

std::string InetAddress::toIpPort() const {
    return toIp() + ":" + std::to_string(port());
}
