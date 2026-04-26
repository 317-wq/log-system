#include "log_formatter.h"
#include <iostream>
#include <fstream>

int main() {
    std::cout << "=== Test LogFormatter ===" << std::endl;

    // 创建日志文件
    std::ofstream logFile("../log/test_formatter.log", std::ios::app);
    if (!logFile) {
        std::cerr << "Failed to open log file!" << std::endl;
        return 1;
    }

    ljt::LogFormatter formatter("[%d][%p][%t][%f:%l] %m");

    ljt::LogEvent::ptr event = std::make_shared<ljt::LogEvent>(
        ljt::LogLevel::INFO,
        __FILE__,
        __LINE__,
        "Test message"
    );

    std::string result = formatter.format(event);

    logFile << result << std::endl;
    std::cout << result << std::endl;

    logFile.close();
    std::cout << "Log written to ../log/test_formatter.log" << std::endl;
    std::cout << "All tests passed!" << std::endl;
    return 0;
}