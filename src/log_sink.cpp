#include "log_sink.h"
#include <cstdio>

namespace ljt {

ConsoleSink::ConsoleSink() {
}

void ConsoleSink::log(const std::string& msg) {
    fprintf(stdout, "%s\n", msg.c_str());
}

void ConsoleSink::flush() {
    fflush(stdout);
}

FileSink::FileSink(const std::string& fileName)
    : m_fileName(fileName) {
    m_file = fopen(fileName.c_str(), "a");
    if (!m_file) {
        m_file = stdout;
    }
}

FileSink::~FileSink() {
    if (m_file && m_file != stdout) {
        fclose(m_file);
    }
}

void FileSink::log(const std::string& msg) {
    if (m_file) {
        fprintf(m_file, "%s\n", msg.c_str());
    }
}

void FileSink::flush() {
    if (m_file) {
        fflush(m_file);
    }
}

}