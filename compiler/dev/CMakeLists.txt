cmake_minimum_required(VERSION 3.16.3)
project(CBit-Compiler)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/frontend)

target_link_libraries(frontend)

add_executable(cbit main.cpp)