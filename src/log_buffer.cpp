#include "../include/log_buffer.h"

namespace ljt {
    LogBuffer::LogBuffer()
        : _curBuffer(_bufferA), _curSize(0) {
    }

    void LogBuffer::push(const char* data, size_t len) {
        // 如果当前缓冲区空间不足，切换到下一个缓冲区
        if (_curSize + len > DEFAULT_SIZE) {
            swap();
        }

        // 如果数据比整个缓冲区还大，就不处理了（简化版本）
        if (len > DEFAULT_SIZE) {
            return;
        }

        // 拷贝数据到当前缓冲区
        memcpy(_curBuffer + _curSize, data, len);
        _curSize += len;
    }

    void LogBuffer::swap() {
        // 交换读写缓冲区
        if (_curBuffer == _bufferA) {
            _curBuffer = _bufferB;
        } else {
            _curBuffer = _bufferA;
        }
        _curSize = 0;
    }

    void LogBuffer::clear() {
        memset(_curBuffer, 0, DEFAULT_SIZE);
        _curSize = 0;
    }

    const char* LogBuffer::data() const {
        return _curBuffer;
    }

    size_t LogBuffer::length() const {
        return _curSize;
    }

    bool LogBuffer::empty() const {
        return _curSize == 0;
    }
}