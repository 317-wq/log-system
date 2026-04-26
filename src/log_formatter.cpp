#include "log_formatter.h"
#include "log_level.h"
#include "utils.h"

namespace ljt {

LogFormatter::LogFormatter(const std::string& pattern)
    : m_pattern(pattern) {
}

std::string LogFormatter::format(LogEvent::ptr event) {
    std::string result = m_pattern;

    std::string timeStr = event->getTime();
    std::string levelStr = LogLevelUtil::toString(event->getLevel());
    std::string threadIdStr = std::to_string(event->getThreadId());
    std::string fileStr = event->getFile();
    std::string lineStr = std::to_string(event->getLine());
    std::string msgStr = event->getMessage();

    size_t pos = 0;
    while ((pos = result.find("%d", pos)) != std::string::npos) {
        result.replace(pos, 2, timeStr);
        pos += timeStr.length();
    }

    pos = 0;
    while ((pos = result.find("%p", pos)) != std::string::npos) {
        result.replace(pos, 2, levelStr);
        pos += levelStr.length();
    }

    pos = 0;
    while ((pos = result.find("%t", pos)) != std::string::npos) {
        result.replace(pos, 2, threadIdStr);
        pos += threadIdStr.length();
    }

    pos = 0;
    while ((pos = result.find("%f", pos)) != std::string::npos) {
        result.replace(pos, 2, fileStr);
        pos += fileStr.length();
    }

    pos = 0;
    while ((pos = result.find("%l", pos)) != std::string::npos) {
        result.replace(pos, 2, lineStr);
        pos += lineStr.length();
    }

    pos = 0;
    while ((pos = result.find("%m", pos)) != std::string::npos) {
        result.replace(pos, 2, msgStr);
        pos += msgStr.length();
    }

    return result;
}

}