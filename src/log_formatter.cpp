#include "../include/log_formatter.h"
#include <cstring>

/*
    日志消息格式化模块
    1、将Event模块的字段自定义格式化为string字符串
*/
namespace ljt {

    LogFormatter::LogFormatter(const LogEvent::ptr &event)
        : _event(event) {
    }

    // 格式化 -> 硬编码
    // [INFO][时间][线程号][文件路径][行号] "message"
    std::string LogFormatter::format() {
        std::string str;

        // FATAL等级 输出红色信息
        // WARN等级 输出紫色信息
        // ERROR等级 输出黄色信息
        const char* color_code = "";
        switch (_event->getLevel()) {
        case LogLevel::FATAL:
            color_code = "\033[31m";
            break;
        case LogLevel::WARN:
            color_code = "\033[35m";
            break;
        case LogLevel::ERROR:
            color_code = "\033[33m";
            break;
        default:
            color_code = "\033[0m";
            break;
        }

        str += color_code;
        str += "[";
        str += LogLevelUtil::toString(_event->getLevel());
        str += "]";
        str += "\033[0m";

        str += "[";
        str += _event->getTime();
        str += "]";

        str += "[";
        str += std::to_string(_event->getThreadId());
        str += "]";

        str += "[";
        str += _event->getFile();
        str += "]";

        str += "[";
        str += std::to_string(_event->getLine());
        str += "]";

        str += " ";
        str += _event->getMessage();
        str += "\033[0m";

        return str;
    }

}