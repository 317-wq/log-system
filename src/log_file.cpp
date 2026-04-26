#include "log_file.h"
#include <cstdio>

namespace ljt {

LogFile::LogFile(const std::string& fileName)
    : m_fileName(fileName) {
    // 打开文件，以追加模式写入
    m_file = fopen(fileName.c_str(), "a");
    if (!m_file) {
        m_file = stdout; // 如果打开失败，输出到控制台
    }
}

LogFile::~LogFile() {
    // 关闭文件
    if (m_file && m_file != stdout) {
        fclose(m_file);
    }
}

void LogFile::write(const std::string& msg) {
    // 写入日志
    if (m_file) {
        fprintf(m_file, "%s\n", msg.c_str());
    }
}

void LogFile::flush() {
    // 刷新缓冲区
    if (m_file) {
        fflush(m_file);
    }
}

}