#pragma once

#include <string>

namespace ljt {

enum class LogLevel {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class LogLevelUtil {
public:
    static const char* toString(LogLevel level);
    static LogLevel fromString(const std::string& str);
};

}