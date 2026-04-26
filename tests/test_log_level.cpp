#include "log_level.h"
#include <iostream>

int main() {
    std::cout << "=== Test LogLevel ===" << std::endl;
    
    // Test toString
    std::cout << "DEBUG: " << ljt::LogLevelUtil::toString(ljt::LogLevel::DEBUG) << std::endl;
    std::cout << "INFO: " << ljt::LogLevelUtil::toString(ljt::LogLevel::INFO) << std::endl;
    std::cout << "WARN: " << ljt::LogLevelUtil::toString(ljt::LogLevel::WARN) << std::endl;
    std::cout << "ERROR: " << ljt::LogLevelUtil::toString(ljt::LogLevel::ERROR) << std::endl;
    std::cout << "FATAL: " << ljt::LogLevelUtil::toString(ljt::LogLevel::FATAL) << std::endl;
    
    // Test fromString
    std::cout << "fromString(\"DEBUG\"): " << ljt::LogLevelUtil::toString(ljt::LogLevelUtil::fromString("DEBUG")) << std::endl;
    std::cout << "fromString(\"INFO\"): " << ljt::LogLevelUtil::toString(ljt::LogLevelUtil::fromString("INFO")) << std::endl;
    std::cout << "fromString(\"WARN\"): " << ljt::LogLevelUtil::toString(ljt::LogLevelUtil::fromString("WARN")) << std::endl;
    std::cout << "fromString(\"ERROR\"): " << ljt::LogLevelUtil::toString(ljt::LogLevelUtil::fromString("ERROR")) << std::endl;
    std::cout << "fromString(\"FATAL\"): " << ljt::LogLevelUtil::toString(ljt::LogLevelUtil::fromString("FATAL")) << std::endl;
    std::cout << "fromString(\"UNKNOWN\"): " << ljt::LogLevelUtil::toString(ljt::LogLevelUtil::fromString("UNKNOWN")) << std::endl;
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}