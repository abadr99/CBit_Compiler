/**
 * @file OptionParser.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
