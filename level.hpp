#pragma once
#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

#include <string>
#include <iostream>

/*
    实现日志等级类
    1、枚举日志等级
    2、日志等级进行字符串级别的转换
*/

namespace ljt{
    class LogLevel{
    public:
        enum class Value{
            DEBUG = 0,
            INFO,
            WARN,
            ERROR,
            FATAL,
            OFF
        };

        static std::string toString(LogLevel::Value val){
            switch(val){
                case Value::DEBUG: return "DEBUG";
                case Value::INFO: return "INFO";
                case Value::WARN: return "WARN";
                case Value::ERROR: return "ERROR";
                case Value::FATAL: return "FATAL";
                case Value::OFF: return "OFF";
            }
            return "UNKNOWN";
        }
    };
}
#endif