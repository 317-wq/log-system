#include "log_event.h"

namespace ljt {

LogEvent::LogEvent(LogLevel level,
                   const std::string& file,
                   int32_t line,
                   const std::string& msg)
    : m_level(level)
    , m_file(file)
    , m_line(line)
    , m_message(msg)
    , m_time(Utils::getCurrentTime())
    , m_threadId(Utils::getThreadId()) {
    // 构造函数，初始化成员变量
    // 自动获取当前时间和线程ID
}

}