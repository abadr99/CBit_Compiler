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
#include "common/OptionParser.hpp"

using namespace cbit::options;

int main(int argc, char* argv[]) {
    // Parse all option through command line and fill data in `CompilerOption`
    // according to parsed data.
    OptionParser op(argc, argv);
    
    // TODO(@abadr): Combine frontend process to one class
    // Run frontend process
    
    // TODO(@abadr): Combine middle-end process to one class
    // Run middle-end process
    
    // TODO(@abadr): Combine backend process to one class
    // Run backend process
}
