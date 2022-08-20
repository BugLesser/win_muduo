cmake_minimum_required(VERSION 3.0.0)
project(bland VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -O2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/third_party/wepoll.c)

add_executable(${PROJECT_NAME} ${SRC_FILES} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
