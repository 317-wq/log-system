#include "log_file.h"
#include <cstdio>

namespace ljt {

LogFile::LogFile(const std::string& fileName)
    : m_fileName(fileName) {
    m_file = fopen(fileName.c_str(), "a");
    if (!m_file) {
        m_file = stdout;
    }
}

LogFile::~LogFile() {
    if (m_file && m_file != stdout) {
        fclose(m_file);
    }
}

void LogFile::write(const std::string& msg) {
    if (m_file) {
        fprintf(m_file, "%s\n", msg.c_str());
    }
}

void LogFile::flush() {
    if (m_file) {
        fflush(m_file);
    }
}

}