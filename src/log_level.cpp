#include "../include/log_level.h"

namespace ljt {
    // 类型转换
    std::string LogLevelUtil::toString(LogLevel level) {
        // 日志级别到字符串的映射
        switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
        }
    }
}