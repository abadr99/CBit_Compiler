/**
 * @file CompilerOptions.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMPILER_DEV_INC_COMMON_COMPILEROPTIONS_HPP_
#define COMPILER_DEV_INC_COMMON_COMPILEROPTIONS_HPP_

#include <string>
#include <vector>

namespace cbit {
namespace options {

class CompilerOptions {
 public:
  void AddFile(const std::string& fileName);
  std::vector<std::string> GetCompiledFiles() const;
  static CompilerOptions& GetCompilerOptions();
 private:
  CompilerOptions();
  CompilerOptions(const CompilerOptions& other) = delete;
  void operator=(const CompilerOptions& other)  = delete;
  static CompilerOptions* pCompilerOptions_;
  std::vector<std::string> files_;
  // TODO(@abadr99): std::vector<> optimisations_;
};

}  // namespace options
}  // namespace cbit

#endif  // COMPILER_DEV_INC_COMMON_COMPILEROPTIONS_HPP_
