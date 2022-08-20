#include <iostream>

#include "event_loop.h"
#include "tcp_server.h"

int main(int, char**) {
    EventLoop loop;

    TcpServer server(&loop, InetAddress("0.0.0.0", 9090));

    std::cout << InetAddress("0.0.0.0", 9090).toIpPort();

    server.setConnectionCallback([](TcpConnection *conn) {
        std::cout << "new connection...\n";
    });

    server.setThreadNum(1);
    server.start();

    loop.run();
}
