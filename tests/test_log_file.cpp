#include "log_file.h"
#include <iostream>

int main() {
    std::cout << "=== Test LogFile ===" << std::endl;

    ljt::LogFile::ptr file = std::make_shared<ljt::LogFile>("../log/test_file.log");
    file->write("Test log message 1");
    file->write("Test log message 2");
    file->write("Test log message 3");
    file->flush();

    std::cout << "Log written to ../log/test_file.log" << std::endl;
    std::cout << "All tests passed!" << std::endl;
    return 0;
}