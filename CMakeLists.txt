cmake_minimum_required(VERSION 3.10)
project(logutil_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR})

# 源文件
add_executable(test
    test.cpp
)
