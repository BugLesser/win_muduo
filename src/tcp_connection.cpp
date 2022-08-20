#include "tcp_connection.h"

#include "channel.h"
#include "socket.h"
#include "buffer.h"

TcpConnection::TcpConnection(EventLoop *loop, Socket *socket)
: loop_(loop)
, socket_(socket)
, channel_(new Channel(loop, socket->sockfd()))
, inputBuffer_(new Buffer())
, outputBuffer_(new Buffer()) {
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

void TcpConnection::startHandleEvent() {
    channel_->enableReading();
    channel_->enableWriting();
    channel_->enableClosing();
    channel_->enableErroring();
}


void TcpConnection::handleRead() {
    int saveErrno = 0;
    inputBuffer_->clear();
    int n = inputBuffer_->readSocket(socket_->sockfd(), &saveErrno);
    if(n <= 0) {
        // error or closed
        return;
    }
    if(messageCallback_) {
        messageCallback_(this, inputBuffer_);
    }
}

void TcpConnection::handleWrite() {

}

void TcpConnection::handleClose() {

}

void TcpConnection::handleError() {

}