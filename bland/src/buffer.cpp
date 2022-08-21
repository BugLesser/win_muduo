#include "buffer.h"

#include "socket.h"

void Buffer::clear() {
    // buffer_.clear();
    readIndex_ = 0;
    writeIndex_ = 0;
}

void Buffer::writeBytes(const char* bytes, size_t size) {
    assert(writeableBytes() >= size);
    for(size_t i = 0; i < size; i++) {
        buffer_[writeIndex_ + i] = bytes[i];
    }
    writeIndex_ += size;
}

template <class T>
void Buffer::writeBytes(const T& val) {
    writeBytes(reinterpret_cast<const char*>(&val), sizeof(T));
}
void Buffer::writeInt8(int8_t x) {
    writeBytes<int8_t>(x);
}
void Buffer::writeUInt8(uint8_t x) {
    writeBytes<uint8_t>(x);
}
void Buffer::writeInt16(int16_t x) {
    writeBytes<int16_t>(x);
}
void Buffer::writeUInt16(uint16_t x) {
    writeBytes<uint16_t>(x);
}
void Buffer::writeInt32(int32_t x) {
    writeBytes<int32_t>(x);
}
void Buffer::writeUInt32(uint32_t x) {
    writeBytes<uint32_t>(x);
}
void Buffer::writeInt64(int64_t x) {
    writeBytes<int64_t>(x);
}
void Buffer::writeUInt64(uint64_t x) {
    writeBytes<uint64_t>(x);
}
void Buffer::writeFloat(float x) {
    writeBytes<float>(x);
}
void Buffer::writeDouble(double x) {
    writeBytes<double>(x);
}
void Buffer::writeString(const std::string& str) {
    writeBytes(str.c_str(), str.length());
}



const char* Buffer::readBytes(char* buf, size_t size) {
    assert(readableBytes() >= size);
    for(size_t i = 0; i < size; i++) {
        buf[i] = buffer_[readIndex_ + i];
    }
    readIndex_ += size;
    return buf;
}

template <class T>
T Buffer::readBytes() {
    T result;
    readBytes((char*)&result, sizeof(T));
    return result;
}

int8_t Buffer::readInt8() {
    return readBytes<int8_t>();
}

uint8_t Buffer::readUInt8() {
    return readBytes<uint8_t>();
}

int16_t Buffer::readInt16() {
    return readBytes<int16_t>();
}

uint16_t Buffer::readUInt16() {
    return readBytes<uint16_t>();
}
int32_t Buffer::readInt32() {
    return readBytes<int32_t>();
}
uint32_t Buffer::readUInt32() {
    return readBytes<uint32_t>();
}
int64_t Buffer::readInt64() {
    return readBytes<int64_t>();
}
uint64_t Buffer::readUInt64() {
    return readBytes<uint64_t>();
}
float Buffer::readFloat() {
    return readBytes<float>();
}
double Buffer::readDouble() {
    return readBytes<double>();
}
std::string Buffer::readString(size_t length) {
    char* s = new char[length + 1];
    s[length] = '\0';
    readBytes(s, length);
    std::string result;
    result.assign(s, length);
    delete[] s;
    return result;
}

int Buffer::readSocket(Socket* socket, int* saveErrno) {
    auto size = writeableBytes();
    char *buf = new char[size];
    int n = socket_ops::read(socket->sockfd(), buf, size, 0);
    if(n <= 0) {
        *saveErrno = errno;
    } else {
        writeBytes(buf, size);
    }
    delete[] buf;
    return n;
}


size_t Buffer::readableBytes() const noexcept {
    return writeIndex_ - readIndex_;
}

size_t Buffer::writeableBytes() const noexcept {
    return buffer_.size() - writeIndex_;
}

std::vector<char>& Buffer::getBuffer() noexcept {
    return buffer_;
}
size_t Buffer::getReadIndex() const noexcept {
    return readIndex_;
}
size_t Buffer::getWriteIndex() const noexcept {
    return writeIndex_;
}

