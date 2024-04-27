#include "common/OptionParser.hpp"

using namespace cbit::options;

OptionParser::OptionParser(int argc, char* argv[]) : argc_(argc), argv_(argv) {
    for (int i = 0 ; i < argc ; ++i) {
        CompilerOptions::GetCompilerOptions().AddFile(argv[i]);
    }
}

CompilerOptions& OptionParser::GetOptions() const {
    return CompilerOptions::GetCompilerOptions();
}
