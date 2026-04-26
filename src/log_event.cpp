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
}

}