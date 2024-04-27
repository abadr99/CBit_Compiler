cmake_minimum_required(VERSION 3.16.3)
project(CBit-Compiler)

set(libs common frontend)
# -- SET COMPILER OPTIONS
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -g -Werror -std=c++17)

# -- ADD AND LINK `frontend` DIR
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dev/src/frontend)
target_link_libraries(frontend)

# -- ADD AND LINK `common` DIR
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dev/src/common)
target_link_libraries(common)

# -- GENERATE 'cbit' binary
add_executable(cbit ${CMAKE_SOURCE_DIR}/dev/main.cpp)
target_include_directories(cbit PRIVATE ${CMAKE_SOURCE_DIR}/dev/inc)
target_link_libraries(cbit ${libs}) # -- LINK 'cbit' BINARY WITH GENETATED LIBS

# ==============================================================================
# --------------------------------- TESTS -------------------------------------
# ==============================================================================
# -- GET ALL TEST SOURCES
file(GLOB_RECURSE src ${CMAKE_CURRENT_LIST_DIR}/tests/*.cpp)
# -- COMPILE FILES
add_executable(cbit-tests ${src})
# -- INCLUDE LIB
target_include_directories(cbit-tests PRIVATE ${CMAKE_SOURCE_DIR}/dev/inc)

# -- LINK 'cbit-tests' BINARY WITH GENETATED LIBS
find_package(GTest REQUIRED)
target_link_libraries(cbit-tests gtest pthread ${libs})

