#include "log_formatter.h"
#include "log_level.h"
#include "utils.h"

namespace ljt {

LogFormatter::LogFormatter(const std::string& pattern)
    : m_pattern(pattern) {
    // 构造日志格式化器
}

std::string LogFormatter::format(LogEvent::ptr event) {
    std::string result = m_pattern;

    // 获取事件的各种信息
    std::string timeStr = event->getTime();
    std::string levelStr = LogLevelUtil::toString(event->getLevel());
    std::string threadIdStr = std::to_string(event->getThreadId());
    std::string fileStr = event->getFile();
    std::string lineStr = std::to_string(event->getLine());
    std::string msgStr = event->getMessage();

    // 替换格式符
    // %d: 时间
    size_t pos = 0;
    while ((pos = result.find("%d", pos)) != std::string::npos) {
        result.replace(pos, 2, timeStr);
        pos += timeStr.length();
    }

    // %p: 日志级别
    pos = 0;
    while ((pos = result.find("%p", pos)) != std::string::npos) {
        result.replace(pos, 2, levelStr);
        pos += levelStr.length();
    }

    // %t: 线程ID
    pos = 0;
    while ((pos = result.find("%t", pos)) != std::string::npos) {
        result.replace(pos, 2, threadIdStr);
        pos += threadIdStr.length();
    }

    // %f: 文件路径
    pos = 0;
    while ((pos = result.find("%f", pos)) != std::string::npos) {
        result.replace(pos, 2, fileStr);
        pos += fileStr.length();
    }

    // %l: 行号
    pos = 0;
    while ((pos = result.find("%l", pos)) != std::string::npos) {
        result.replace(pos, 2, lineStr);
        pos += lineStr.length();
    }

    // %m: 消息内容
    pos = 0;
    while ((pos = result.find("%m", pos)) != std::string::npos) {
        result.replace(pos, 2, msgStr);
        pos += msgStr.length();
    }

    return result;
}

}