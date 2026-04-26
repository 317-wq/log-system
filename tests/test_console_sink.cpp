#include "log_sink.h"
#include <iostream>

int main() {
    std::cout << "=== Test ConsoleSink ===" << std::endl;

    ljt::ConsoleSink::ptr sink = std::make_shared<ljt::ConsoleSink>();
    sink->log("ConsoleSink test message 1");
    sink->log("ConsoleSink test message 2");
    sink->flush();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}