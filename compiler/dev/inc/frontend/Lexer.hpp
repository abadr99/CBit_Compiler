/**
 * @file Lexer.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef COMPILER_DEV_INC_FRONTEND_LEXER_HPP_ 
#define COMPILER_DEV_INC_FRONTEND_LEXER_HPP_

#include <string>
#include <map>

namespace cbit {
namespace frontend {
namespace lexer {

enum TokenTypes {
    kKeyword,
    kType,
    kId,
    kOperator,
    kSymbols,
    kNumber,
    kString,
    kComment,
    kNewline,
};


class Lexer {
 public:
    explicit Lexer(std::string fileName);
 private:
    std::string fileName_;
};

}  // namespace lexer
}  // namespace frontend
}  // namespace cbit

#endif  // COMPILER_DEV_INC_FRONTEND_LEXER_HPP_
