#pragma once

#include <string>

namespace ljt {

/**
 * 日志级别枚举
 */
enum class LogLevel {
    DEBUG = 0,  // 调试信息
    INFO,       // 一般信息
    WARN,       // 警告信息
    ERROR,      // 错误信息
    FATAL       // 致命错误
};

/**
 * 日志级别工具类，提供级别与字符串的转换
 */
class LogLevelUtil {
public:
    /**
     * 将日志级别转换为字符串
     * @param level 日志级别
     * @return 对应的字符串
     */
    static const char* toString(LogLevel level);
    
    /**
     * 将字符串转换为日志级别
     * @param str 级别字符串
     * @return 对应的日志级别，默认为 INFO
     */
    static LogLevel fromString(const std::string& str);
};

}