/**
 * @file CompilerError.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMPILER_DEV_INC_COMMON_COMPILERREPORTER_HPP_
#define COMPILER_DEV_INC_COMMON_COMPILERREPORTER_HPP_

#include <string>
#include <vector>
#include <memory>

#include "common/Types.hpp"

namespace cbit {
namespace common {
namespace compiler_reporter {

class CompilerMessage {
 public:
  CompilerMessage(std::string fileName, 
                  uint32 lineNumber, 
                  std::string msg);
  virtual void Print() = 0;
  virtual ~CompilerMessage() = default;
 protected:
  std::string file_name_;
  uint32      line_number_;
  std::string msg_;
  std::string color_;
};

class CompilerError : public CompilerMessage {
 public:
  CompilerError(std::string fileName, uint32 lineNumber, std::string msg);
  void Print() override;
};

class CompilerWarning : public CompilerMessage {
 public:
  CompilerWarning(std::string fileName, uint32 lineNumber, std::string msg);
  void Print() override;
};

class CompilerInfo : public CompilerMessage {
 public:
  CompilerInfo(std::string fileName, uint32 lineNumber, std::string msg);
  void Print() override;
};

using pCompilerError   = std::unique_ptr<CompilerError>;
using pCompilerWarning = std::unique_ptr<CompilerWarning>;
using pCompilerInfo    = std::unique_ptr<CompilerInfo>;

class CompilerAbort {
 public:
  static void Abort(std::string fileName, std::string msg);
};

class CompilerReporter {
 public:
  using message_t = std::vector<std::unique_ptr<CompilerMessage>>;
  static CompilerReporter& Get();
  void Add(std::unique_ptr<CompilerMessage> cm);
  const message_t& GetMessages() const;
  void Report() const;
 private:
  CompilerReporter() = default;
  CompilerReporter(const CompilerReporter&) = delete;
  void operator=(const CompilerReporter&) = delete;
  static CompilerReporter* pCompilerReporter;
  message_t messages_;
};

}  // namespace compiler_reporter
}  // namespace common
}  // namespace cbit

#endif  // COMPILER_DEV_INC_COMMON_COMPILERREPORTER_HPP_
