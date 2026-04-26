#pragma once

#include <string>
#include <memory>

namespace ljt {

/**
 * 日志输出接口，定义日志输出的抽象类
 */
class LogSink {
public:
    using ptr = std::shared_ptr<LogSink>;
    
    /**
     * 析构函数
     */
    virtual ~LogSink() = default;
    
    /**
     * 输出日志
     * @param msg 日志内容
     */
    virtual void log(const std::string& msg) = 0;
    
    /**
     * 刷新缓冲区
     */
    virtual void flush() = 0;
};

/**
 * 控制台输出类，将日志输出到控制台
 */
class ConsoleSink : public LogSink {
public:
    /**
     * 构造控制台输出
     */
    ConsoleSink();
    
    /**
     * 输出日志到控制台
     * @param msg 日志内容
     */
    void log(const std::string& msg) override;
    
    /**
     * 刷新控制台缓冲区
     */
    void flush() override;
};

/**
 * 文件输出类，将日志输出到文件
 */
class FileSink : public LogSink {
public:
    /**
     * 构造文件输出
     * @param fileName 文件路径
     */
    explicit FileSink(const std::string& fileName);
    
    /**
     * 析构函数，关闭文件
     */
    ~FileSink() override;
    
    /**
     * 输出日志到文件
     * @param msg 日志内容
     */
    void log(const std::string& msg) override;
    
    /**
     * 刷新文件缓冲区
     */
    void flush() override;

private:
    std::string m_fileName; // 文件路径
    FILE* m_file;          // 文件指针
};

}