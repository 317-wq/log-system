#pragma once
/*
    主要用户异步日志记录器的双缓冲区，这里我们采用生成消费模型
    业务线程写入日志消息放在自己的缓冲区，后台线程将日志信息读取到自己的缓冲区
    还有什么一堆判断条件，比如缓冲区是否为空，是否已满等，都需要在代码中进行处理
*/
#include <string>
#include <cstring>
#include <memory>

namespace ljt {
    // 日志缓冲区 - 双缓冲设计
    class LogBuffer {
    public:
        using ptr = std::shared_ptr<LogBuffer>;

        // 默认缓冲区大小 4KB
        static const size_t DEFAULT_SIZE = 4096;

        LogBuffer();
        ~LogBuffer() = default;

        // 追加数据到缓冲区
        // 如果当前缓冲区空间不足，自动切换到下一个缓冲区
        void push(const char* data, size_t len);

        // 交换读写缓冲区
        // 主线程和后台线程调用
        void swap();

        // 清空当前缓冲区
        void clear();

        // 获取数据指针
        const char* data() const;

        // 获取数据长度
        size_t length() const;

        // 检查是否为空
        bool empty() const;

    private:
        // 两个缓冲区
        char _bufferA[DEFAULT_SIZE];
        char _bufferB[DEFAULT_SIZE];

        // 当前正在写入的缓冲区
        char* _curBuffer;

        // 当前缓冲区已使用的大小
        size_t _curSize;
    };
}