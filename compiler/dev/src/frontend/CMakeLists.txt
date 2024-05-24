set(SRC
    Lexer.cpp
    Token.cpp
)

message(STATUS "Building and linking ${SRC}")

add_library(frontend ${SRC})
target_include_directories(frontend PRIVATE ${PROJECT_SOURCE_DIR}/dev/inc)