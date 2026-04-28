#pragma once
/*
    日志消息格式化模块
    1、将Event模块的字段自定义格式化为string字符串
*/

#include "log_event.h"
#include "log_level.h"

namespace ljt {
    class LogFormatter {
    public:
        LogFormatter(const LogEvent::ptr &event);

        // 格式化 -> 硬编码
        // [INFO][时间][线程号][文件路径][行号] "message"
        std::string format();

    private:
        LogEvent::ptr _event;
    };
}