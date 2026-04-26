#include "message.hpp"
#include <iostream>

int main() {
    ljt::LogMsg msg("test_logger", "test.cpp", 10, "hello world", ljt::LogLevel::Value::INFO);
    std::cout << "Message created successfully\n";
    std::cout << "Level: " << ljt::LogLevel::toString(msg._level) << "\n";
    std::cout << "Name: " << msg._name << "\n";
    std::cout << "File: " << msg._file << "\n";
    std::cout << "Line: " << msg._line << "\n";
    std::cout << "Payload: " << msg._payload << "\n";
    std::cout << "All tests passed!" << std::endl;
    return 0;
}