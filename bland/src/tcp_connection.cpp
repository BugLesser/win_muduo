#include "tcp_connection.h"

#include "channel.h"
#include "socket.h"
#include "buffer.h"

#include "logging.h"

TcpConnection::TcpConnection(EventLoop *loop, 
                            Socket *socket,
                            const InetAddress& localAddr,
                            const InetAddress& peerAddr)
: loop_(loop)
, socket_(socket)
, channel_(new Channel(loop, socket->sockfd()))
, inputBuffer_(new Buffer())
, outputBuffer_(new Buffer())
, localAddr_(localAddr)
, peerAddr_(peerAddr) {
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));
}

TcpConnection::~TcpConnection() {
    if(socket_) delete socket_;
    if(channel_) delete channel_;
    if(inputBuffer_) delete inputBuffer_;
    if(outputBuffer_) delete outputBuffer_;
}

void TcpConnection::send(const char* buf, int len) {
    socket_->write(buf, len);
}

void TcpConnection::startHandleEvent() {
    channel_->enableReading();
    channel_->enableWriting();
    channel_->enableClosing();
    channel_->enableErroring();
}


void TcpConnection::handleRead() {
    int saveErrno = 0;
    inputBuffer_->clear();
    int n = inputBuffer_->readSocket(socket_, &saveErrno);
    if(n == 0) {
        handleClose();
        return;
    }
    if(n < 0) {
        handleError();
        return;
    }
    if(messageCallback_) {
        messageCallback_(this, inputBuffer_);
    }
}

void TcpConnection::handleWrite() {

}

void TcpConnection::handleClose() {
    channel_->disableAll();
    channel_->remove();
    socket_->close();
    if(closeCallback_) closeCallback_(this);
    LOG(DEBUG, "handle close: %s", peerAddr_.toIpPort().c_str());
}

void TcpConnection::handleError() {
    int err = socket_ops::getSocketError(socket_->sockfd());
    if(err == 0) return;
    LOG(INFO, "handle error [code: %d, msg: %s]", err, strerror(err));
}