#include "../include/log_sink.h"
#include <memory>
#include <stdexcept>
#include <string>

namespace ljt {
    // 基类的静态函数实现
    void LogSink::openFile(std::ofstream& ofs, const std::string &filepath) {
        try {
            Utils::createFileDir(filepath);
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }

        ofs.open(filepath, std::ios::app);
        if (!ofs.is_open()) {
            throw std::runtime_error("Failed to open file: " + filepath);
        }
    }

    // 控制台输出子类的实现
    void ConsoleSink::log(const std::string &msg) {
        std::cout.write(msg.c_str(), msg.size());
    }

    // 输出到单文件子类的实现
    FileSink::FileSink(const std::string &filepath)
        : _filepath(filepath) {
        openFile(_ofs, filepath);
    }

    FileSink::~FileSink() {
        _ofs.flush();
        _ofs.close();
    }

    void FileSink::log(const std::string &msg) {
        _ofs.write(msg.c_str(), msg.size());
        _ofs.flush();
        if (_ofs.good() == false) {
            throw std::runtime_error("File write failed: " + _filepath);
        }
    }

    // 文件滚动更新策略
    RollSinkBySize::RollSinkBySize(const std::string &basename, size_t maxsize)
        : _basename(basename), _maxsize(maxsize), _id(1), _cur_size(0) {
    }

    RollSinkBySize::~RollSinkBySize() {
        _ofs.flush();
        _ofs.close();
    }

    void RollSinkBySize::log(const std::string &msg) {
        // 检查是否需要切换文件
        if (_cur_size + msg.size() > _maxsize) {
            // 关闭当前文件
            if (_ofs.is_open()) {
                _ofs.flush();
                _ofs.close();
            }
            // 切换到下一个文件
            _id++;
            _cur_size = 0;
        }

        // 如果文件未打开，则打开新文件
        if (!_ofs.is_open()) {
            std::string filename = _basename + "-" + std::to_string(_id);
            openFile(_ofs, filename);
        }

        // 写入数据
        _ofs.write(msg.c_str(), msg.size());
        _ofs.flush();
        _cur_size += msg.size();

        if (_ofs.good() == false) {
            throw std::runtime_error("RollSinkBySize write failed");
        }
    }

    // 简单工厂，基类指针指向派生类对象
    template<typename SinkType, typename ...Args>
    LogSink::ptr getSink(Args&& ...args){
        return std::make_shared<SinkType>(std::forward<Args>(args)...); // 完美转发，保持性质
    }
}