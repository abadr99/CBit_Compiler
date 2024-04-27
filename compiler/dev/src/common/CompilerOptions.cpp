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