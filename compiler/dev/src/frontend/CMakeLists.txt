set (src
     lexer.cpp
    )

message(STATUS "Building and linking frontend stage files")

add_library(frontend ${src})
target_include_directories(frontend PUBLIC ${CMAKE_PROJECT_DIR}/inc)