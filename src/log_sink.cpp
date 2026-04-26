#include "log_sink.h"
#include <cstdio>

namespace ljt {

ConsoleSink::ConsoleSink() {
}

void ConsoleSink::log(const std::string& msg) {
    fprintf(stdout, "%s\n", msg.c_str());
}

void ConsoleSink::flush() {
    fflush(stdout);
}

}