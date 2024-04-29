#include <gtest/gtest.h>
#include "common/CompilerOptions.hpp"
#include "common/OptionParser.hpp"

using namespace cbit::options;

TEST(OptionParser, files) {
    // Set argc and argv as command arguments by assuming the command is
    // cbit path/to/file1.c path/to/file2.c
    int argc = 3;
    const char* argv[] = {"cbit", "path/to/file1.c", "path/to/file2.c"};
    
    OptionParser op(argc,const_cast<char**>(argv));
    auto& opts = op.GetOptions();

    EXPECT_STREQ(opts.GetCompiledFiles()[0].c_str(), "path/to/file1.c");
    EXPECT_STREQ(opts.GetCompiledFiles()[1].c_str(), "path/to/file2.c");
}

