cmake_minimum_required(VERSION 3.10)
project(log_system)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(utils src/utils.cpp)
add_library(log_level src/log_level.cpp)
add_library(log_event src/log_event.cpp)
target_link_libraries(log_event utils log_level)

add_executable(test_utils tests/test_utils.cpp)
target_link_libraries(test_utils utils)

add_executable(test_log_level tests/test_log_level.cpp)
target_link_libraries(test_log_level log_level)

add_executable(test_log_event tests/test_log_event.cpp)
target_link_libraries(test_log_event log_event)
