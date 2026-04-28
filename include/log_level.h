#pragma once
/*
    实现日志等级模块
    1、将枚举类型转换为字符串
*/
#include <string>
#include <iostream>

namespace ljt {
    enum class LogLevel {
        DEBUG = 0, // 调试信息
        INFO,      // 一般信息
        WARN,      // 警告信息
        ERROR,     // 错误信息
        FATAL      // 致命错误
    };

    class LogLevelUtil {
    public:
        static std::string toString(LogLevel level);
    };
}