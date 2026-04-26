#pragma once

#include <string>
#include <cstdint>

namespace ljt {

/**
 * 工具类，提供通用工具函数
 */
class Utils {
public:
    /**
     * 获取当前时间，默认格式：YYYY-MM-DD HH:MM:SS
     * @return 格式化后的时间字符串
     */
    static std::string getCurrentTime();
    
    /**
     * 获取当前时间，使用自定义格式
     * @param format 时间格式字符串（如 "%Y-%m-%d %H:%M:%S"）
     * @return 格式化后的时间字符串
     */
    static std::string getCurrentTime(const std::string& format);
    
    /**
     * 获取当前线程ID
     * @return 线程ID的哈希值
     */
    static uint64_t getThreadId();
    
    /**
     * 从文件路径中提取文件名
     * @param filePath 文件路径
     * @return 文件名
     */
    static std::string getFileName(const std::string& filePath);
};

}