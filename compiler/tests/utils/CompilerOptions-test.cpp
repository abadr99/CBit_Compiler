#include <gtest/gtest.h>
#include "common/CompilerOptions.hpp"

using namespace cbit::common::options;

TEST(CompilerOptions, Options) {
    // Set argc and argv as command arguments by assuming the command is
    // cbit path/to/file1.c path/to/file2.c
    int argc = 5;
    const char* argv[] = {"cbit", 
                          "path/to/file1.c", 
                          "path/to/file2.c", 
                          "-o", "keep_lexer=1"};
    CompilerOptions::GetCompilerOptions().ParseCommandLine(argc, const_cast<char**>(argv));
    auto options = CompilerOptions::GetCompilerOptions().GetOptions();
    ASSERT_NE(options.find("keep_lexer"), options.end());
    auto opt = options.at("keep_lexer");
    EXPECT_EQ(opt.GetName(), "keep_lexer");
    EXPECT_EQ(opt.GetValue(), "1");
}
