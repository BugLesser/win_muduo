#pragma once


#include <ctime>
#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <cstring>

struct SourceLocation {
    const char* filename;
    int line;
    SourceLocation();
    SourceLocation(const char* filename, int line): filename(filename), line(line) {}
};

#undef ERROR

class Logging {
public:
    enum class Level : int {
        FATAL = 0,
        ERROR,
        WARN,
        INFO,
        DEBUG,
        TRACE,
    };
    Logging(FILE* fp = stdout) {
        open(fp);
    }
    Level getLevel() const noexcept { return level_; }
    void setLevel(Level level) noexcept { level_ = level; }
    void open(FILE* fp, Level level = Level::INFO) {
        assert(fp != 0);
        setLevel(level);
        fp_ = fp;
    }

    int log(SourceLocation loc, Level level, const char* fmt, ...);
    // int log(SourceLocation loc, Level level, const std::string& msg);

    // int fatal(const char* fmt, ...);
    // int error(const char* fmt, ...);
    // int warn(const char* fmt, ...);
    // int info(const char* fmt, ...);
    // int debug(const char* fmt, ...);
    // int trace(const char* fmt, ...);
private:
    Level level_;
    FILE* fp_;
};



/*
    FATAL = 0,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,
*/
static const char* getLevelName(Logging::Level level) {
    switch (level) {
    case Logging::Level::FATAL: return "fatal";
    case Logging::Level::ERROR: return "error";
    case Logging::Level::WARN: return "warn";
    case Logging::Level::INFO: return "info";
    case Logging::Level::DEBUG: return "debug";
    case Logging::Level::TRACE: return "trace";
    }
    return "";
}


static time_t lastLogSeconds = 0;
static char lastTimeFormatStr[1024] = { 0 };
static int lastTimeFormatStrLen = 0;
int Logging::log(SourceLocation loc, Level level, const char* fmt, ...) {
    if(level_ < level) {
        return 0;
    }
    // Timestamp now = Timestamp::now();
    time_t seconds = time(NULL);
    char buf[1024] = { 0 };
    char* ptr = buf;
    int len;
    if(lastLogSeconds != seconds) {
        tm* tm = localtime(&seconds);
        len = snprintf(ptr, sizeof(buf), "[%04d-%02d-%02d %02d:%02d:%02d] ", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        lastLogSeconds = seconds;
        strncpy(lastTimeFormatStr, buf, len);
        lastTimeFormatStrLen = len;
        ptr += len;
    } else {
        strncpy(buf, lastTimeFormatStr, lastTimeFormatStrLen);
        ptr += lastTimeFormatStrLen;
    }

    len = snprintf(ptr, sizeof(buf) - (ptr - buf), "[%s] [%s:%d] ", getLevelName(level), loc.filename, loc.line);
    ptr += len;

    
    va_list ap;
    va_start(ap, fmt);

    len = vsnprintf(ptr, sizeof(buf) - (ptr - buf), fmt, ap);
    ptr += len;

    va_end(ap);

    *ptr++ = '\n';
    *ptr = '\0';

    len = ptr - buf;

    fwrite(buf, len, 1, fp_);

    return 0;
}


static Logging* defaultLogger = nullptr;

Logging* getDefaultLogger() {
    if(defaultLogger == nullptr) {
        defaultLogger = new Logging();
    }
    return defaultLogger;
}

void setDefaultLogger(Logging* logger) {
    defaultLogger = logger;
}

#if defined(DISABLE_LOGGING)
#define LOG(level, ...)
#else
#define LOG(level, ...) getDefaultLogger()->log(SourceLocation{__FILE__, __LINE__}, Logging::Level::level, ##__VA_ARGS__)
#endif