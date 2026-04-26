#pragma once

#include <string>
#include <memory>

namespace ljt {

class LogSink {
public:
    using ptr = std::shared_ptr<LogSink>;
    virtual ~LogSink() = default;
    virtual void log(const std::string& msg) = 0;
    virtual void flush() = 0;
};

class ConsoleSink : public LogSink {
public:
    ConsoleSink();
    void log(const std::string& msg) override;
    void flush() override;
};

}