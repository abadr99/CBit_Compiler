/**
 * @file CompilerOptions.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <vector>
#include <unordered_map>
#include "common/Options.def"

namespace cbit {
namespace common {
namespace options {

class Option {
 public:
    using OptionVal  = std::string;
    using OptionName = std::string;
    Option(OptionName type, OptionVal val);
    Option(const Option& other);
    OptionName GetName()  const;
    OptionVal  GetValue() const;
    void SetName(OptionName name);
    void SetValue(OptionVal val);
 private:
    OptionName name_;
    OptionVal  val_;
};

class CompilerOptions {
 public:
    using Options_t    = std::unordered_map<std::string, Option>;
    using Files_t      = std::vector<std::string>;
    
    static CompilerOptions& GetCompilerOptions();
    
    void ParseCommandLine(int argc, char* argv[]);
    Files_t     GetFiles()     const;
    Options_t   GetOptions()   const;
    std::string GetOptionVal(const Option& opt) const;
 private:
    CompilerOptions();
    CompilerOptions(const CompilerOptions& other) = delete;
    void operator=(const CompilerOptions& other)  = delete;
    static CompilerOptions* pCompilerOptions_;

    void ParseOption(std::string optStr);
    void PrintHelpMsg();
    Options_t          opts_;
    Files_t            files_;
};

}   // namespace options
}   // namespace common
}   // namespace cbit