#include "tcp_server.h"

#include <thread>
#include <cassert>

#include "event_loop.h"
#include "event_loop_thread.h"
#include "event_loop_thread_pool.h"
#include "acceptor.h"
#include "tcp_connection.h"

TcpServer::TcpServer(EventLoop* loop, const InetAddress& bindAddr)
: loop_(loop)
, acceptor_(new Acceptor(loop, bindAddr))
, threadPool_(new EventLoopThreadPool(loop)) {
    acceptor_->setNewConnectionCallback(
        std::bind(&TcpServer::handleNewConnection, this, std::placeholders::_1, std::placeholders::_2)
    );
}

void TcpServer::start() {
    assert(!acceptor_->listening());
    acceptor_->listen(64);
    threadPool_->start();
}

void TcpServer::handleNewConnection(Socket *socket, const InetAddress& peerAddr) {

    EventLoop* loop = threadPool_->getNextLoop();

    TcpConnection* connection = new TcpConnection(loop, socket);
    connection->setConnectionCallback(connectionCallback_);
    connection->setMessageCallback(messageCallback_);
    connection->setWriteCompleteCallback(writeCompleteCallback_);
    connection->setCloseCallback(closeCallback_);
    connection->startHandleEvent();

    if(connectionCallback_) {
        connectionCallback_(connection);
    }
}

void TcpServer::setThreadNum(int threadNum) {
    threadPool_->setThreadNum(threadNum);
}
