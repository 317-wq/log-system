#pragma once

#include "log_event.h"
#include <memory>
#include <string>

namespace ljt {

class LogFormatter {
public:
    using ptr = std::shared_ptr<LogFormatter>;

    explicit LogFormatter(const std::string& pattern);

    std::string format(LogEvent::ptr event);

private:
    std::string m_pattern;
};

}