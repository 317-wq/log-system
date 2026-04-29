#include "../include/log_logger.h"
#include <cstdarg>
#include <cstdio>
#include <mutex>

namespace ljt {
    // 全局日志器定义
    LogLogger::ptr g_logger;

    // 基类的格式化函数实现
    std::string LogLogger::formatLog(LogEvent::ptr event) {
        LogFormatter::ptr formatter = std::make_shared<LogFormatter>(event);
        return formatter->format();
    }

    SyncLogLogger::SyncLogLogger(LogSink::ptr sink)
        : _sink(sink) {
    }

    SyncLogLogger::~SyncLogLogger() {
    }

    void SyncLogLogger::log(LogLevel level, const std::string& file, int32_t line,
                            const std::string& msg, ...) {
        // 处理可变参数
        va_list args;
        va_start(args, msg);

        // 使用 vsnprintf 格式化可变参数
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), msg.c_str(), args);
        va_end(args);

        // 初始化日志事件
        LogEvent::ptr logEvent = std::make_shared<LogEvent>(level, file, line, buffer);
        // 格式化日志事件
        std::string format_msg = formatLog(logEvent);
        // 立即输出到 Sink
        _sink->log(format_msg);
    }

    AsyncLogLogger::AsyncLogLogger(LogSink::ptr sink)
        : _sink(sink)
        , _exit(false)
        , _buffer(std::make_shared<LogBuffer>()) {
        // 启动后台线程
        _thread = std::thread(&AsyncLogLogger::worker, this);
    }

    AsyncLogLogger::~AsyncLogLogger() {
        // 设置退出标志
        _exit = true;
        // 唤醒后台线程
        _cond.notify_all();
        // 等待后台线程结束
        if (_thread.joinable()) {
            _thread.join();
        }
    }

    void AsyncLogLogger::log(LogLevel level, const std::string& file, int32_t line,
                             const std::string& msg, ...) {
        // 处理可变参数
        va_list args;
        va_start(args, msg);

        // 使用 vsnprintf 格式化可变参数
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), msg.c_str(), args);
        va_end(args);

        // 初始化日志事件
        LogEvent::ptr logEvent = std::make_shared<LogEvent>(level, file, line, buffer);
        // 格式化日志事件
        std::string format_msg = formatLog(logEvent);

        // 加锁，将日志放入缓冲区
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _buffer->push(format_msg.c_str(), format_msg.size());
        }

        // 唤醒后台线程
        _cond.notify_one();
    }

    void AsyncLogLogger::worker() {
        while (true) {
            std::string msg;

            // 加锁，等待新数据或退出
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _cond.wait(lock, [this] {
                    return !_buffer->empty() || _exit;
                });

                // 如果退出标志且缓冲区为空，退出循环
                if (_exit && _buffer->empty()) {
                    break;
                }

                // 取出缓冲区数据
                if (!_buffer->empty()) {
                    msg = std::string(_buffer->data(), _buffer->length());
                    _buffer->clear();
                }
            }

            // 写出日志（锁外）
            if (!msg.empty()) {
                _sink->log(msg);
            }
        }
    }
}