#include "log_sink.h"
#include <cstdio>

namespace ljt {

ConsoleSink::ConsoleSink() {
    // 构造控制台输出
}

void ConsoleSink::log(const std::string& msg) {
    // 输出日志到控制台
    fprintf(stdout, "%s\n", msg.c_str());
}

void ConsoleSink::flush() {
    // 刷新控制台缓冲区
    fflush(stdout);
}

FileSink::FileSink(const std::string& fileName)
    : m_fileName(fileName) {
    // 打开文件，以追加模式写入
    m_file = fopen(fileName.c_str(), "a");
    if (!m_file) {
        m_file = stdout; // 如果打开失败，输出到控制台
    }
}

FileSink::~FileSink() {
    // 关闭文件
    if (m_file && m_file != stdout) {
        fclose(m_file);
    }
}

void FileSink::log(const std::string& msg) {
    // 输出日志到文件
    if (m_file) {
        fprintf(m_file, "%s\n", msg.c_str());
    }
}

void FileSink::flush() {
    // 刷新文件缓冲区
    if (m_file) {
        fflush(m_file);
    }
}

}