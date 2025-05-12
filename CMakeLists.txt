cmake_minimum_required(VERSION 3.28)
project(cpp-lib)

set(CMAKE_CXX_STANDARD 20)

add_library(cpplib INTERFACE)
target_include_directories(cpplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cpplib)