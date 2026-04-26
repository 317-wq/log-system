#include "log_formatter.h"
#include "log_level.h"
#include "utils.h"

namespace ljt {

LogFormatter::LogFormatter(const std::string& pattern)
    : m_pattern(pattern) {
}

std::string LogFormatter::format(LogEvent::ptr event) {
    std::string result = m_pattern;

    std::string timeStr = event->getTime();     // %d: 时间
    std::string levelStr = LogLevelUtil::toString(event->getLevel());  // %p: 日志级别
    std::string threadIdStr = std::to_string(event->getThreadId());  // %t: 线程ID
    std::string fileStr = event->getFile();    // %f: 文件路径
    std::string lineStr = std::to_string(event->getLine());  // %l: 行号
    std::string msgStr = event->getMessage();  // %m: 消息内容

    size_t pos = 0;
    // 替换时间
    while ((pos = result.find("%d", pos)) != std::string::npos) {
        result.replace(pos, 2, timeStr);
        pos += timeStr.length();
    }

    pos = 0;
    // 替换日志级别
    while ((pos = result.find("%p", pos)) != std::string::npos) {
        result.replace(pos, 2, levelStr);
        pos += levelStr.length();
    }

    pos = 0;
    // 替换线程ID
    while ((pos = result.find("%t", pos)) != std::string::npos) {
        result.replace(pos, 2, threadIdStr);
        pos += threadIdStr.length();
    }

    pos = 0;
    // 替换文件路径
    while ((pos = result.find("%f", pos)) != std::string::npos) {
        result.replace(pos, 2, fileStr);
        pos += fileStr.length();
    }

    pos = 0;
    // 替换行号
    while ((pos = result.find("%l", pos)) != std::string::npos) {
        result.replace(pos, 2, lineStr);
        pos += lineStr.length();
    }

    pos = 0;
    // 替换消息内容
    while ((pos = result.find("%m", pos)) != std::string::npos) {
        result.replace(pos, 2, msgStr);
        pos += msgStr.length();
    }

    return result;
}

}