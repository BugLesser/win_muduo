#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <cassert>


class Socket;

class Buffer {
public:
    static const size_t kInitialSize = 1024;
public:
    explicit Buffer(size_t initialSize = kInitialSize)
    : buffer_(initialSize)
    , readIndex_(0)
    , writeIndex_(0) { }

    explicit Buffer(const std::string& data)
    : buffer_(data.begin(), data.end())
    , readIndex_(0)
    , writeIndex_(data.size()) { }

    explicit Buffer(const std::vector<char>& data)
    : buffer_(data.begin(), data.end())
    , readIndex_(0)
    , writeIndex_(data.size()) { }

    Buffer(const char* buf, size_t len)
    : buffer_(buf, buf + len)
    , readIndex_(0)
    , writeIndex_(len) { }

    void clear();

    void writeBytes(const char* bytes, size_t size);
    template <class T> void writeBytes(const T& val);
    void writeInt8(int8_t x);
    void writeUInt8(uint8_t x);
    void writeInt16(int16_t x);
    void writeUInt16(uint16_t x);
    void writeInt32(int32_t x);
    void writeUInt32(uint32_t x);
    void writeInt64(int64_t x);
    void writeUInt64(uint64_t x);
    void writeFloat(float x);
    void writeDouble(double x);
    void writeString(const std::string&);

    const char* readBytes(char* buf, size_t size);
    template <class T> T readBytes();
    int8_t readInt8();
    uint8_t readUInt8();
    int16_t readInt16();
    uint16_t readUInt16();
    int32_t readInt32();
    uint32_t readUInt32();
    int64_t readInt64();
    uint64_t readUInt64();
    float readFloat();
    double readDouble();
    std::string readString(size_t length);

    int readSocket(Socket *socket, int* saveErrno);

    size_t readableBytes() const noexcept;
    size_t writeableBytes() const noexcept;

    std::vector<char>& getBuffer() noexcept;
    size_t getReadIndex() const noexcept;
    size_t getWriteIndex() const noexcept;
private:
    std::vector<char> buffer_;
    size_t readIndex_;
    size_t writeIndex_;
};
