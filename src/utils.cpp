#include "../include/utils.h"
#include <cstddef>
#include <ctime>
#include <sys/stat.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>

namespace ljt {
    // 获取线程id的唯一标识
    uint64_t Utils::getThreadId() {
        return static_cast<uint64_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
    }

    // 获取当前格式化时间
    std::string Utils::getCurrentTime() {
        std::string format = "%Y-%m-%d %H:%M:%S";
        // 距1970-01-01的秒数
        time_t tloc = time(0);
        // 进一步转换为tm结构体
        struct tm result;
        localtime_r(&tloc, &result);
        // strftime转换
        char buffer[64];
        strftime(buffer, sizeof buffer - 1, format.c_str(), &result);

        return std::string(buffer);
    }

    // 获取文件目录
    std::string Utils::getFileDir(const std::string &filepath) {
        size_t pos = filepath.find_last_of("/\\");

        // 直接就是文本文件
        if (pos == std::string::npos) {
            return "";
        }

        // 目录部分带最后的/
        // test/test.txt
        std::string substr = filepath.substr(0, pos + 1);
        return substr;
    }

    // 创建文件目录，文件的话，后续fstream会自己处理的
    void Utils::createFileDir(const std::string &filepath) {
        std::string dirpath = getFileDir(filepath);
        // 这个是文本文件的情况，不需要创建
        if (dirpath.empty()) {
            return;
        }

        // 逐目录创建
        // ./test/test0/test.txt
        size_t pos = 0, idx = 0;
        while (idx < dirpath.size()) {
            pos = dirpath.find_first_of("/\\", idx);
            // 找不到更多分隔符，说明已经处理完毕
            if (pos == std::string::npos) {
                break;
            }

            std::string substr = dirpath.substr(0, pos + 1);
            idx = pos + 1;

            // 创建目录
            if (mkdir(substr.c_str(), 0777) != 0) {
                // 如果目录已存在，不算错误
                if (errno != EEXIST) {
                    throw std::runtime_error("Failed to create directory: " + substr +
                                             ", error: " + std::strerror(errno));
                }
            }
        }
    }
}