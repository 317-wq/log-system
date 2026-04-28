#pragma once
/*
    日志事件模块
    1、初始化一条消息的字段
*/

#include "log_level.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <memory>

namespace ljt {
    class LogEvent {
    public:
        // 智能指针管理
        using ptr = std::shared_ptr<LogEvent>;

        LogEvent(LogLevel level,
                const std::string& file,
                int32_t line,
                const std::string& message);

        // 获取日志等级
        LogLevel getLevel() {
            return m_level;
        }

        // 获取文件路径
        const std::string &getFile() {
            return m_file;
        }

        // 获取行号
        int32_t getLine() {
            return m_line;
        }

        // 获取消息内容
        const std::string &getMessage() {
            return m_message;
        }

        // 获取时间
        const std::string &getTime() {
            return m_time;
        }

        // 获取线程id
        uint64_t getThreadId() {
            return m_threadId;
        }

    private:
        LogLevel m_level;      // 日志级别
        std::string m_file;    // 文件路径
        int32_t m_line;        // 行号
        std::string m_message; // 消息内容
        std::string m_time;    // 时间
        uint64_t m_threadId;   // 线程ID
    };
}