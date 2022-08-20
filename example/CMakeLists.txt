cmake_minimum_required(VERSION 3.0.0)
project(bland_example)

include_directories(../bland/include)

file(GLOB SRC_FILES *.cpp)

add_executable(bland_example ${SRC_FILES})

target_link_libraries(bland_example bland)
