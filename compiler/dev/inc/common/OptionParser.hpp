/**
 * @file OptionParser.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMPILER_DEV_INC_COMMON_OPTIONPARSER_HPP_
#define COMPILER_DEV_INC_COMMON_OPTIONPARSER_HPP_

#include "common/CompilerOptions.hpp"

namespace cbit {
namespace options {

class OptionParser {
 public:
  OptionParser(int argc, char* argv[]);
  CompilerOptions& GetOptions() const;
 private:
  int argc_;
  char** argv_;
};

}   // namespace options
}   // namespace cbit

#endif  // COMPILER_DEV_INC_COMMON_OPTIONPARSER_HPP_
