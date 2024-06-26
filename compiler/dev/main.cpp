/**
 * @file main.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include "common/CompilerReporter.hpp"
#include "common/CompilerOptions.hpp"
#include "frontend/Lexer.hpp"

using namespace cbit::common::compiler_reporter;
using namespace cbit::common::options;

using Lexer = cbit::frontend::lexer::Lexer;

int main(int argc, char* argv[]) {
    CompilerOptions::GetCompilerOptions().ParseCommandLine(argc, argv);
        
    // TODO(@abadr): Combine frontend process to one class
    // Run frontend process
    for (auto file : CompilerOptions::GetCompilerOptions().GetFiles()) {
        Lexer lex(file);
    }
    // check if we have a lexer errors and terminate
    if (CompilerReporter::Get().GetMessages().size()) {
        CompilerReporter::Get().Report();
        std::abort();
    }
    // TODO(@abadr): Combine middle-end process to one class
    // Run middle-end process
    
    // TODO(@abadr): Combine backend process to one class
    // Run backend process
}
