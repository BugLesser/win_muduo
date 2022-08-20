#pragma once

#include "socket_ops.h"

#include <string>
#include <cstdint>

class InetAddress {
public:

    InetAddress(const std::string& ip, uint16_t port, bool ipv6 = false);

    InetAddress(const in_addr_type& addr)
    : addr_(addr) {
    }

    InetAddress(const in6_addr_type& addr)
    : addr6_(addr) {
    }

    short family() const noexcept { return addr_.sin_family; }
    uint16_t port() const noexcept { return ::htons(addr_.sin_port); }
    const socket_addr_type* sockAddr() const noexcept;

    std::string toIp() const;
    std::string toIpPort() const;
private:
    bool ipv6_;
    union {
        in_addr_type addr_;
        in6_addr_type addr6_;
    };
};

