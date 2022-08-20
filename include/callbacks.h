#pragma once

#include <functional>

class TcpServer;
class TcpConnection;
class Socket;
class InetAddress;
class Buffer;

using ChannelEventCallback = std::function<void()>;

using ConnectionCallback = std::function<void(TcpConnection*)>;
using MessageCallback = std::function<void(TcpConnection*, Buffer*)>;
using WriteCompleteCallback = std::function<void(TcpConnection*)>;
using CloseCallback = std::function<void(TcpConnection*)>;
using ErrorCallback = std::function<void(TcpConnection*)>;

using NewConnectionCallback = std::function<void (Socket*, const InetAddress&)>;