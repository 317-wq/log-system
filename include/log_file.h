#pragma once

#include <string>
#include <memory>

namespace ljt {

class LogFile {
public:
    using ptr = std::shared_ptr<LogFile>;

    explicit LogFile(const std::string& fileName);
    ~LogFile();

    void write(const std::string& msg);
    void flush();

private:
    std::string m_fileName;
    FILE* m_file;
};

}