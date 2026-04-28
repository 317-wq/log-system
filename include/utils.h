#pragma once
/*
    这个模块就是实现一些通用的功能
    1、获取当前的 年月日 时分秒 格式时间
    2、获取线程id
    3、获取文件目录
    4、对文件目录进行创建 -> 避免耦合性高，就把34分开来写了
*/

#include <thread>
#include <iostream>
#include <string>

// 类内静态函数声明一次static就行了，实现不需要写static

namespace ljt {
    class Utils {
    public:
        // 获取线程id
        static uint64_t getThreadId();

        // 获取当前格式化时间
        static std::string getCurrentTime();

        // 获取文件目录
        static std::string getFileDir(const std::string& filepath);

        // 创建文件目录，文件的话，后续fstream会自己处理的
        // 这边的filepath就是上面那个函数处理过来的
        static void createFileDir(const std::string& filepath);
    };
}