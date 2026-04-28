#include "../include/log_event.h"

namespace ljt {
    LogEvent::LogEvent(LogLevel level,
                        const std::string &file,
                        int32_t line,
                        const std::string &message)
        :m_level(level),
        m_file(file),
        m_line(line),
        m_message(message),
        m_threadId(Utils::getThreadId()),
        m_time(Utils::getCurrentTime())
    {
    }

}