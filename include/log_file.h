#pragma once

#include <string>
#include <memory>

namespace ljt {

/**
 * 日志文件类，管理日志文件的写入
 */
class LogFile {
public:
    using ptr = std::shared_ptr<LogFile>;

    /**
     * 构造日志文件
     * @param fileName 文件路径
     */
    explicit LogFile(const std::string& fileName);
    
    /**
     * 析构函数，关闭文件
     */
    ~LogFile();

    /**
     * 写入日志
     * @param msg 日志内容
     */
    void write(const std::string& msg);
    
    /**
     * 刷新缓冲区
     */
    void flush();

private:
    std::string m_fileName; // 文件路径
    FILE* m_file;          // 文件指针
};

}