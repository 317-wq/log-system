cmake_minimum_required(VERSION 3.10)
project(LogSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件
set(SOURCES
    src/utils.cpp
    src/log_level.cpp
    src/log_event.cpp
    src/log_formatter.cpp
    src/log_sink.cpp
    src/log_buffer.cpp
    src/log_logger.cpp
)

# 构建静态库
add_library(log STATIC ${SOURCES})

# 链接线程库
target_link_libraries(log pthread)

# 可选：构建测试程序
option(BUILD_TEST "Build test program" ON)

if(BUILD_TEST)
    add_executable(test_log_sink test_log_sink.cpp)
    target_link_libraries(test_log_sink log pthread)
endif()
