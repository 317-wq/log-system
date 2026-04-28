cmake_minimum_required(VERSION 3.10)
project(ljt_logger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/utils.cpp
    src/log_level.cpp
    src/log_event.cpp
    src/log_formatter.cpp
    src/log_sink.cpp
)

add_library(logger ${SOURCES})

add_executable(test_log_sink test_log_sink.cpp)
target_link_libraries(test_log_sink logger)