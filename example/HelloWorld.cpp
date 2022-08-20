#include <iostream>

#include "event_loop.h"
#include "tcp_server.h"
#include "tcp_connection.h"

int main(int argc, const char** argv) {

    EventLoop loop;

    TcpServer server(&loop, InetAddress("0.0.0.0", 9090));

    server.setConnectionCallback([](TcpConnection *conn) {
        std::cout << "new connection: " << conn->peerAddress().toIpPort() << std::endl;
    });

    server.setThreadNum(1);
    server.start();
    loop.run();
    return 0;
}