#include "./include/log_sink.h"
#include <iostream>
#include <ctime>

// 用户自定义的按时间滚动的 Sink
class MyRollSinkByTime : public ljt::LogSink {
public:
    MyRollSinkByTime(const std::string& basename)
        : _basename(basename), _last_time(0) {
    }

    virtual void log(const std::string &msg) override {
        time_t now = time(nullptr);
        tm* t = localtime(&now);
        int current_hour = t->tm_hour;

        // 跨小时了，需要切换文件
        if (current_hour != _last_time) {
            if (_ofs.is_open()) {
                _ofs.flush();
                _ofs.close();
            }
            _last_time = current_hour;

            // 生成文件名：basename-YYYYMMDD-HH
            char buf[32];
            strftime(buf, sizeof(buf), "%Y%m%d-%H", t);
            _filename = _basename + "-" + buf;

            // 使用基类的 openFile
            ljt::LogSink::openFile(_ofs, _filename);
        }

        // 如果文件未打开（第一次或切换后）
        if (!_ofs.is_open()) {
            char buf[32];
            strftime(buf, sizeof(buf), "%Y%m%d-%H", t);
            _filename = _basename + "-" + buf;
            ljt::LogSink::openFile(_ofs, _filename);
            _last_time = current_hour;
        }

        _ofs.write(msg.c_str(), msg.size());
        _ofs.flush();
    }

    ~MyRollSinkByTime() {
        if (_ofs.is_open()) {
            _ofs.flush();
            _ofs.close();
        }
    }

private:
    std::string _basename;
    std::string _filename;
    std::ofstream _ofs;
    int _last_time;
};

int main() {
    std::cout << "Testing LogSink" << std::endl;
    std::cout << "====================================" << std::endl;

    // 测试 ConsoleSink
    std::cout << "Test 1: ConsoleSink" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    ljt::LogSink::ptr console = std::make_shared<ljt::ConsoleSink>();
    console->log("Hello Console\n");
    console->log("Another line\n");

    // 测试 FileSink
    std::cout << "Test 2: FileSink" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    ljt::LogSink::ptr file = std::make_shared<ljt::FileSink>("./test_file.txt");
    file->log("Hello File 1\n");
    file->log("Hello File 2\n");

    // 测试 RollSinkBySize
    std::cout << "Test 3: RollSinkBySize (max 50 bytes)" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    ljt::LogSink::ptr roll = std::make_shared<ljt::RollSinkBySize>("./roll_test", 50);
    roll->log("0123456789");   // 10 bytes
    roll->log("0123456789");   // 10 bytes, total 20
    roll->log("0123456789");   // 10 bytes, total 30
    roll->log("0123456789");   // 10 bytes, total 40
    roll->log("0123456789");   // 10 bytes, total 50
    roll->log("0123456789");   // 10 bytes, should roll to file-2

    // 测试用户自定义的 RollSinkByTime
    std::cout << "Test 4: User-defined RollSinkByTime" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    ljt::LogSink::ptr myRoll = std::make_shared<MyRollSinkByTime>("./time_test");
    myRoll->log("Message at hour X\n");
    myRoll->log("Another message\n");

    std::cout << "====================================" << std::endl;
    std::cout << "Test completed!" << std::endl;

    return 0;
}