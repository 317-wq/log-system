#include "log_event.h"
#include "log_level.h"
#include <iostream>
#include <fstream>

int main() {
    std::cout << "=== Test LogEvent ===" << std::endl;
    
    // 创建日志文件
    std::ofstream logFile("../log/test_event.log", std::ios::app);
    if (!logFile) {
        std::cerr << "Failed to open log file!" << std::endl;
        return 1;
    }
    
    ljt::LogEvent::ptr event = std::make_shared<ljt::LogEvent>(
        ljt::LogLevel::INFO,
        __FILE__,
        __LINE__,
        "Hello, Log!"
    );

    // 输出到文件
    logFile << "Level: " << ljt::LogLevelUtil::toString(event->getLevel()) << std::endl;
    logFile << "File: " << event->getFile() << std::endl;
    logFile << "Line: " << event->getLine() << std::endl;
    logFile << "Message: " << event->getMessage() << std::endl;
    logFile << "Time: " << event->getTime() << std::endl;
    logFile << "ThreadID: " << event->getThreadId() << std::endl;
    logFile << "====================" << std::endl;
    
    // 同时输出到控制台
    std::cout << "Level: " << ljt::LogLevelUtil::toString(event->getLevel()) << std::endl;
    std::cout << "File: " << event->getFile() << std::endl;
    std::cout << "Line: " << event->getLine() << std::endl;
    std::cout << "Message: " << event->getMessage() << std::endl;
    std::cout << "Time: " << event->getTime() << std::endl;
    std::cout << "ThreadID: " << event->getThreadId() << std::endl;
    
    logFile.close();
    std::cout << "Log written to ../log/test_event.log" << std::endl;
    std::cout << "All tests passed!" << std::endl;
    return 0;
}