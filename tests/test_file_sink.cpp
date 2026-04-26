#include "log_sink.h"
#include <iostream>

int main() {
    std::cout << "=== Test FileSink ===" << std::endl;

    ljt::FileSink::ptr sink = std::make_shared<ljt::FileSink>("../log/test_file_sink.log");
    sink->log("FileSink test message 1");
    sink->log("FileSink test message 2");
    sink->log("FileSink test message 3");
    sink->flush();

    std::cout << "Log written to ../log/test_file_sink.log" << std::endl;
    std::cout << "All tests passed!" << std::endl;
    return 0;
}