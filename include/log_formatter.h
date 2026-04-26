#pragma once

#include "log_event.h"
#include <memory>
#include <string>

namespace ljt {

/**
 * 日志格式化类，将 LogEvent 转换为字符串
 */
class LogFormatter {
public:
    using ptr = std::shared_ptr<LogFormatter>;

    /**
     * 构造日志格式化器
     * @param pattern 格式字符串，支持的格式符：
     * - %d: 时间
     * - %p: 日志级别
     * - %t: 线程ID
     * - %f: 文件路径
     * - %l: 行号
     * - %m: 消息内容
     */
    explicit LogFormatter(const std::string& pattern);

    /**
     * 格式化日志事件
     * @param event 日志事件
     * @return 格式化后的字符串
     */
    std::string format(LogEvent::ptr event);

private:
    std::string m_pattern; // 格式字符串
};

}