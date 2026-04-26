#pragma once

#include <string>
#include <cstdint>

namespace ljt {

class Utils {
public:
    static std::string getCurrentTime();
    static std::string getCurrentTime(const std::string& format);
    static uint64_t getThreadId();
    static std::string getFileName(const std::string& filePath);
};

}