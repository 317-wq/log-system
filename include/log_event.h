#pragma once

#include "log_level.h"
#include "utils.h"
#include <memory>
#include <string>

namespace ljt {

/**
 * 日志事件类，封装一次日志请求的数据
 */
class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;

    /**
     * 构造日志事件
     * @param level 日志级别
     * @param file 文件路径
     * @param line 行号
     * @param msg 消息内容
     */
    LogEvent(LogLevel level,
             const std::string& file,
             int32_t line,
             const std::string& msg);

    /**
     * 获取日志级别
     * @return 日志级别
     */
    LogLevel getLevel() const { return m_level; }
    
    /**
     * 获取文件路径
     * @return 文件路径
     */
    const std::string& getFile() const { return m_file; }
    
    /**
     * 获取行号
     * @return 行号
     */
    int32_t getLine() const { return m_line; }
    
    /**
     * 获取消息内容
     * @return 消息内容
     */
    const std::string& getMessage() const { return m_message; }
    
    /**
     * 获取时间
     * @return 时间字符串
     */
    const std::string& getTime() const { return m_time; }
    
    /**
     * 获取线程ID
     * @return 线程ID
     */
    uint64_t getThreadId() const { return m_threadId; }

private:
    LogLevel m_level;      // 日志级别
    std::string m_file;    // 文件路径
    int32_t m_line;        // 行号
    std::string m_message; // 消息内容
    std::string m_time;    // 时间
    uint64_t m_threadId;   // 线程ID
};

}