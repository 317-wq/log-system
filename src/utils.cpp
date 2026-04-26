#include "utils.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <thread>

namespace ljt {

std::string Utils::getCurrentTime() {
    return getCurrentTime("%Y-%m-%d %H:%M:%S");
}

std::string Utils::getCurrentTime(const std::string& format) {
    // 获取当前系统时间
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    // 格式化时间
    std::stringstream ss;
    struct tm tm_buf;
    localtime_r(&time_t, &tm_buf);
    ss << std::put_time(&tm_buf, format.c_str());
    return ss.str();
}

uint64_t Utils::getThreadId() {
    // 获取线程ID的哈希值
    return static_cast<uint64_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
}

std::string Utils::getFileName(const std::string& filePath) {
    // 从路径中提取文件名
    size_t pos = filePath.find_last_of("/\\");
    if (pos == std::string::npos) {
        return filePath;
    }
    return filePath.substr(pos + 1);
}

}