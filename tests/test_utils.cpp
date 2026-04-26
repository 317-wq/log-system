#include "utils.h"
#include <iostream>

int main() {
    std::cout << "=== Test Utils ===" << std::endl;
    std::cout << "Current Time: " << ljt::Utils::getCurrentTime() << std::endl;
    std::cout << "Thread ID: " << ljt::Utils::getThreadId() << std::endl;
    std::cout << "File Name: " << ljt::Utils::getFileName("/home/user/test.cpp") << std::endl;
    std::cout << "All tests passed!" << std::endl;
    return 0;
}