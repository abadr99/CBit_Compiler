#ifndef _COMPILER_OPTIONS_H_
#define _COMPILER_OPTIONS_H_

#include <string>
#include <vector>

namespace cbit {
namespace options{

class CompilerOptions {
 public:
  void AddFile(const std::string& fileName);
  std::vector<std::string> GetCompiledFiles() const;
  static CompilerOptions& GetCompilerOptions();
 private:
  CompilerOptions();
  CompilerOptions(CompilerOptions& other) = delete;
  void operator=(CompilerOptions& other)  = delete;
  static CompilerOptions* pCompilerOptions_;
  std::vector<std::string> files_;
  // TODO(@abadr99): std::vector<> optimisations_;
};

}
}

#endif // _COMPILER_OPTIONS_H_