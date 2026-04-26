#pragma once

#include "log_level.h"
#include "utils.h"
#include <memory>
#include <string>

namespace ljt {

class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;

    LogEvent(LogLevel level,
             const std::string& file,
             int32_t line,
             const std::string& msg);

    LogLevel getLevel() const { return m_level; }
    const std::string& getFile() const { return m_file; }
    int32_t getLine() const { return m_line; }
    const std::string& getMessage() const { return m_message; }
    const std::string& getTime() const { return m_time; }
    uint64_t getThreadId() const { return m_threadId; }

private:
    LogLevel m_level;
    std::string m_file;
    int32_t m_line;
    std::string m_message;
    std::string m_time;
    uint64_t m_threadId;
};

}