#pragma once

/*
    这个模块就是日志输出器部分，选择你的日志信息输出到哪里
    1、控制台输出 console -> stdout
    2、输出到固定一个文件里面
    3、采取滚动刷新输出到文件 -> 按固定的最大字节数来判断
    4、扩展 -> 模版函数，用户自定义形式，可以按时间...

    采取简单工厂模式
*/

#include "utils.h"
#include <cstddef>
#include <exception>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <cassert>

namespace ljt {
    // 基类
    class LogSink {
    public:
        using ptr = std::shared_ptr<LogSink>;
        virtual void log(const std::string &msg) = 0;
        virtual ~LogSink() {}

    protected:
        static void openFile(std::ofstream& ofs, const std::string &filepath);
    };

    // 控制台输出子类
    class ConsoleSink : public LogSink {
    public:
        virtual void log(const std::string &msg);
    };

    // 输出到单文件的子类
    class FileSink : public LogSink {
    public:
        FileSink(const std::string &filepath);
        ~FileSink();
        virtual void log(const std::string &msg);

    private:
        std::string _filepath;
        std::ofstream _ofs;
    };

    // 采取滚动刷新输出到文件 -> 按固定的最大字节数来判断
    class RollSinkBySize : public LogSink {
    public:
        RollSinkBySize(const std::string& basename, size_t maxsize);
        virtual void log(const std::string& msg);
        ~RollSinkBySize();

    private:
        std::string _basename; // 前缀文本名
        std::ofstream _ofs;
        size_t _maxsize;
        int _id;
        size_t _cur_size;
    };

    // 扩展：如果就是用户想自己提供按时间来创建文件的话
    // 我们不可能让他去改源代码的，因此，我们这边提供一个简单工厂模式
    // 支持用户自己在外面继承一个基类来用
    class SinkFactory{
    public:
        // 不同的sink的参数数量不同，需要传递可变参数包，编译器自己选择应该用什么Sink，重载
        // ...args：声明参数包  args...：展开参数包
        template<typename SinkType, typename ...Args>
        static LogSink::ptr getSink(Args&& ...args) {
            return std::make_shared<SinkType>(std::forward<Args>(args)...); // 完美转发，保持性质
        }
    };
}