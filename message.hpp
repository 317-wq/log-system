#pragma once
#include "util.hpp"
#include "level.hpp"
#include <thread>
// #include <memory>

namespace ljt
{
    struct LogMsg
    {
        size_t _line;           // 行号
        size_t _ctime;          // 时间
        std::thread::id _tid;   // 线程ID
        std::string _name;      // 日志器名称
        std::string _file;      // 文件名
        std::string _payload;   // 日志消息
        LogLevel::Value _level; // 日志等级
        LogMsg(const std::string &name, const std::string &file, size_t line, std::string &&payload,
               LogLevel::Value level)
            : _line(line), _ctime(util::Data::getNowTime()), _tid(std::this_thread::get_id()),
              _name(name), _file(file), _payload(std::move(payload)), _level(level)
        {
            // std::cout << "构造msg\n";
        }
        //~LogMsg() { /*std::cout << "析构msg\n";*/}
    };
}