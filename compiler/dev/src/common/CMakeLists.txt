file(GLOB src "*.cpp")

add_library(common ${src})
target_include_directories(common PRIVATE ${CMAKE_SOURCE_DIR}/dev/inc)