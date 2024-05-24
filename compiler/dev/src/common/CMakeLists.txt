set(SRC
    CompilerOptions.cpp
    CompilerReporter.cpp
)

message(STATUS "Building and linking ${SRC}")
add_library(common ${SRC})
target_include_directories(common PRIVATE ${CMAKE_SOURCE_DIR}/dev/inc)