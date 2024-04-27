#ifndef _OPTION_PARSER_H_
#define _OPTION_PARSER_H_

#include "CompilerOptions.hpp"

namespace cbit {
namespace options{

class OptionParser {
 public:
  OptionParser(int argc, char* argv[]);
  CompilerOptions& GetOptions() const;
 private:
  int argc_;
  char** argv_;
};

}
}

#endif // _OPTION_PARSER_H_