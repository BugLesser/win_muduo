#include <iostream>

#include "event_loop.h"
#include "tcp_server.h"
#include "tcp_connection.h"
#include "buffer.h"

static char resp[] = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Length: 13\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "HelloWorld!!!";

int main(int argc, const char** argv) {

    EventLoop loop;

    TcpServer server(&loop, InetAddress("0.0.0.0", 9090));

    server.setConnectionCallback([](TcpConnection *conn) {
        std::cout << "new connection ==> localAddr: " << conn->localAddress().toIpPort() 
               << ", peerAddr: " << conn->peerAddress().toIpPort() << std::endl;
    });

    server.setMessageCallback([](TcpConnection *conn, Buffer* buffer) {
        conn->send(resp, ::strlen(resp));
    });

    server.setThreadNum(2);
    server.start();
    loop.run();
    return 0;
}