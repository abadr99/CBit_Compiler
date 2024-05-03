set (src
     Lexer.cpp
     Token.cpp
    )

message(STATUS "Building and linking ${src}")

add_library(frontend ${src})
target_include_directories(frontend PRIVATE ${PROJECT_SOURCE_DIR}/dev/inc)