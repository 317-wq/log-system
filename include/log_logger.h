#pragma once

/*
    日志记录模块:控制日志构建的流程，简化用户使用的难度
*/
#include <string>
#include <cstdarg>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "log_event.h"
#include "log_level.h"
#include "log_sink.h"
#include "log_buffer.h"
#include "../include/log_formatter.h"

namespace ljt{
    // 前向声明
    class LogLogger;

    // 基类 - 抽象日志记录器
    // 定义纯虚函数接口，由子类实现
    class LogLogger {
    public:
        using ptr = std::shared_ptr<LogLogger>;

        // 统一的日志接口，level 参数指定日志级别
        virtual void log(LogLevel level, const std::string& file, int32_t line, const std::string& msg, ...) = 0;

        virtual ~LogLogger() = default;

    protected:
        // 供子类使用的格式化函数
        std::string formatLog(LogEvent::ptr event);
    };

    // 全局日志器
    extern LogLogger::ptr g_logger;

    // 同步日志记录器
    // 用于在主线程中同步记录日志
    class SyncLogLogger : public LogLogger {
    public:
        SyncLogLogger(LogSink::ptr sink);
        ~SyncLogLogger() override;

        void log(LogLevel level, const std::string& file, int32_t line, const std::string& msg, ...) override;

    private:
        // 输出到哪里
        LogSink::ptr _sink;
    };

    // 异步日志记录器
    // 用于在后台线程中异步记录日志
    class AsyncLogLogger : public LogLogger {
    public:
        AsyncLogLogger(LogSink::ptr sink);
        ~AsyncLogLogger() override;

        void log(LogLevel level, const std::string& file, int32_t line, const std::string& msg, ...) override;

    private:
        // 后台工作线程函数
        void worker();

    private:
        // 输出到哪里
        LogSink::ptr _sink;

        // 锁资源
        std::mutex _mutex;

        // 条件变量
        std::condition_variable _cond;

        // 后台线程
        std::thread _thread;

        // 退出标志
        bool _exit;

        // 日志缓冲区
        LogBuffer::ptr _buffer;
    };
}

// 初始化全局日志器
// 使用方式: INIT_LOG(ljt::SinkFactory::getSink<ljt::ConsoleSink>());
#define INIT_LOG(sink) ljt::g_logger = std::make_shared<ljt::SyncLogLogger>(sink)
#define INIT_ASYNC_LOG(sink) ljt::g_logger = std::make_shared<ljt::AsyncLogLogger>(sink)

// 日志宏 - 用户调用接口
// 使用方式: LOG_DEBUG("message %d", 123)
#define LOG_DEBUG(msg, ...) ljt::g_logger->log(ljt::LogLevel::DEBUG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...) ljt::g_logger->log(ljt::LogLevel::INFO, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...) ljt::g_logger->log(ljt::LogLevel::WARN, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) ljt::g_logger->log(ljt::LogLevel::ERROR, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_FATAL(msg, ...) ljt::g_logger->log(ljt::LogLevel::FATAL, __FILE__, __LINE__, msg, ##__VA_ARGS__)

// 带 logger 参数的日志宏（保留兼容）
#define LOG_DEBUG_EX(logger, msg, ...) logger->log(ljt::LogLevel::DEBUG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_INFO_EX(logger, msg, ...) logger->log(ljt::LogLevel::INFO, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_WARN_EX(logger, msg, ...) logger->log(ljt::LogLevel::WARN, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_ERROR_EX(logger, msg, ...) logger->log(ljt::LogLevel::ERROR, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_FATAL_EX(logger, msg, ...) logger->log(ljt::LogLevel::FATAL, __FILE__, __LINE__, msg, ##__VA_ARGS__)