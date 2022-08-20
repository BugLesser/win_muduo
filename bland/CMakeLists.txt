set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -O2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/third_party/wepoll.c)

add_library(bland ${SRC_FILES})

target_link_libraries(bland PRIVATE ws2_32)
