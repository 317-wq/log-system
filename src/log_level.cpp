#include "log_level.h"

namespace ljt {

const char* LogLevelUtil::toString(LogLevel level) {
    // 日志级别到字符串的映射
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

LogLevel LogLevelUtil::fromString(const std::string& str) {
    // 字符串到日志级别的映射
    if (str == "DEBUG") return LogLevel::DEBUG;
    if (str == "INFO")  return LogLevel::INFO;
    if (str == "WARN")  return LogLevel::WARN;
    if (str == "ERROR") return LogLevel::ERROR;
    if (str == "FATAL") return LogLevel::FATAL;
    return LogLevel::INFO; // 默认返回 INFO
}

}