#pragma once

#include "callbacks.h"
#include "inet_address.h"

class EventLoop;
class Socket;
class Channel;

class TcpConnection {
public:
    TcpConnection(EventLoop *loop, Socket *socket);

    ~TcpConnection();

    const InetAddress& localAddress();
    const InetAddress& peerAddress();

    void send(const char* buf, int len);
    void send(const std::string& buf);
    void send(Buffer* buf);

    void shutdown();
    void close();

    void setConnectionCallback(ConnectionCallback cb) { connectionCallback_ = std::move(cb); }
    void setMessageCallback(MessageCallback cb) { messageCallback_ = std::move(cb); }
    void setWriteCompleteCallback(WriteCompleteCallback cb) { writeCompleteCallback_ = std::move(cb); }
    void setCloseCallback(CloseCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(ErrorCallback cb) { errorCallback_ = std::move(cb); }

    void startHandleEvent();

    Buffer* inputBuffer() { return inputBuffer_; }
    Buffer* outputBuffer() { return outputBuffer_; }
private:
    EventLoop *loop_;
    Socket *socket_;
    Channel *channel_;
    Buffer *inputBuffer_;
    Buffer *outputBuffer_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    CloseCallback closeCallback_;
    ErrorCallback errorCallback_;

    void handleRead();
    void handleWrite();
    void handleClose();
    void handleError();
};
