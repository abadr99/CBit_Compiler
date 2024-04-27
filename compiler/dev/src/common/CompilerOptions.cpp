/**
 * @file CompilerOptions.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <vector>
#include <string>
#include "common/CompilerOptions.hpp"

using namespace cbit::options;

CompilerOptions* CompilerOptions::pCompilerOptions_  = nullptr;

void CompilerOptions::AddFile(const std::string& fileName) {
    files_.push_back(fileName);
}

std::vector<std::string> CompilerOptions::GetCompiledFiles() const {
    return files_;
}

CompilerOptions& CompilerOptions::GetCompilerOptions() {
    if (pCompilerOptions_ == nullptr) {
        pCompilerOptions_ = new CompilerOptions;
    }
    return *pCompilerOptions_;
}

CompilerOptions::CompilerOptions() { /* PRIVATE EMPTY CTOR */ }
