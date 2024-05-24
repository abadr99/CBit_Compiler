/**
 * @file CompilerOptions.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "common/Types.hpp"
#include "common/Options.def"
#include "common/Assert.hpp"
#include "common/CompilerOptions.hpp"

using namespace cbit::common::options;

// -----------------------------------------------------------------------------
// OPTIONS CLASS
// -----------------------------------------------------------------------------
Option::Option(OptionName name, OptionVal val) : name_(name), val_(val)
{ /* EMPTY */ }

Option::Option(const Option& other) : name_(other.GetName()), val_(other.GetValue())
{ /* EMPTY */ }

typename Option::OptionName Option::GetName() const {
    return name_;
}

typename Option::OptionVal Option::GetValue() const {
    return val_;
}

void Option::SetName(OptionName type) {
    name_ = type;
}

void Option::SetValue(OptionVal val) {
    val_ = val;
}

// -----------------------------------------------------------------------------
// COMPILER-OPTIONS CLASS
// -----------------------------------------------------------------------------
CompilerOptions* CompilerOptions::pCompilerOptions_  = nullptr;
CompilerOptions& CompilerOptions::GetCompilerOptions() {
    if (pCompilerOptions_ == nullptr) {
        pCompilerOptions_ = new CompilerOptions;
    }
    return *pCompilerOptions_;
}

CompilerOptions::CompilerOptions() {
    #define OPT(name_, default_, ignore1, ignore2)\
        opts_.emplace(#name_, Option(#name_, #default_));
    OPTIONS
    #undef OPT
}

void CompilerOptions::ParseCommandLine(int argc, char* argv[]) {
    // -- CONVERT argv TO STRINGS TO DEAL WITH IT IN EASIER WAY
    std::vector<std::string> cmd_line;
    for (int i = 1 ; i < argc ; ++i) {
        cmd_line.push_back(argv[i]);
    }

    // -- RECOGNIZE COMMAND LINE OPTIONS
    for (uint32 i = 0 ; i < cmd_line.size(); ++i) {
        // Parse -- options 
        // syntax: -- option=value
        if (cmd_line[i].compare(0, 2, "--") == 0) {
            ParseOption(cmd_line[i]);
        } else if (cmd_line[i] == "--help") {
            PrintHelpMsg();
        } else {
            files_.push_back(cmd_line[i]);
        }
    }
}

typename CompilerOptions::Files_t CompilerOptions::GetFiles() const {
    return files_;
}

typename CompilerOptions::Options_t CompilerOptions::GetOptions() const {
    return opts_;
}

std::string CompilerOptions::GetOptionVal(const std::string str_opt) const {
    return opts_.at(str_opt).GetValue();
}

bool CompilerOptions::IsEnabled(const std::string str_opt) const {
    std::string opt_val = opts_.at(str_opt).GetValue();
    if (opt_val == "1" || opt_val == "true")  return true;
    if (opt_val == "0" || opt_val == "false") return false;
    CBIT_ASSERT(false, 
                "Calling CompilerOptions::IsEnabled() with non boolean option");
    return false;
}

void CompilerOptions::ParseOption(std::string optStr) {
    std::string opt_name;
    std::string opt_val;
    uint32 i = 2;  // start with second character in order to ignore "--"
    while (optStr[i] != '=') {
        opt_name += optStr[i++];
    }
    // Check if we parse a correct option
    auto it = opts_.find(opt_name);
    if (it == opts_.end()) {
        std::cerr << "[OPTION]: Unknown option " << opt_name << " use --help \n";
        std::abort();
        return;
    }
    // Change the value of option in option map
    opt_val = optStr.substr(i + 1);  // ignore '=' character
    it->second.SetValue(opt_val);
}

void CompilerOptions::PrintHelpMsg() {
    std::string expectedVal;
    #define OPT(name_, ignore1, description_, expected_val_)\
        expectedVal = expected_val_;\
        for (uint32 i = 0 ; i < expectedVal.size(); ++i) {\
            if (expectedVal[i] == ',') {\
                expectedVal.erase(expectedVal.begin() + i);\
                expectedVal.insert(i, "\n\t\t\t");\
                i += 4;\
            }\
        }\
        std::replace(expectedVal.begin(), expectedVal.end(), ',', '\n');\
        std::cout << #name_ << "\t\t" << description_ << "\n\t\t\t " << expectedVal << "\n";
    OPTIONS
    #undef OPT       
}
