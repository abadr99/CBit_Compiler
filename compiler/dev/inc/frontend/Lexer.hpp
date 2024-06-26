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

#include <fstream>
#include <string>
#include <vector>

#include "frontend/Token.hpp"

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
    using Tokens_t   = std::vector<cbit::frontend::token::Token>;
    explicit Lexer(std::string fileName);
    Tokens_t Get() const;
 private:
    using TokenStr_t = std::vector<std::string>;

    std::string fileName_;
    std::ifstream stream_;
    Tokens_t lexemes_;

    void Lex();
    TokenStr_t TokenizeLine(std::string line);
    void AddLexeme(std::string token_str, uint32 lineNumber);
    void GenerateLexFile();
};

}  // namespace lexer
}  // namespace frontend
}  // namespace cbit

#endif  // COMPILER_DEV_INC_FRONTEND_LEXER_HPP_
