cmake_minimum_required(VERSION 3.16.3)
project(CBit-Compiler)

# -- SET COMPILER OPTIONS
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -g -Werror -std=c++17)

# -- ADD AND LINK `frontend` DIR
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/frontend)
target_link_libraries(frontend)

# -- ADD AND LINK `common` DIR
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/common)
target_link_libraries(common)

# -- GENERATE `cbit` BINARY
add_executable(cbit 
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

# -- DEFINE INCLUDE FILES
target_include_directories(cbit PRIVATE ${CMAKE_SOURCE_DIR}/inc)

# -- LINK 'cbit' BINARY WITH GENETATED LIBS
target_link_libraries(cbit common frontend)

