/**
 * @file Token.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMPILER_DEV_INC_FRONTEND_TOKEN_HPP_
#define COMPILER_DEV_INC_FRONTEND_TOKEN_HPP_

#include <variant>
#include <string>

#include "common/Types.hpp"

namespace cbit {
namespace frontend {
namespace token {

enum class TokenType {
    kKeyword,
    kId,
    kOperator,
    kSymbol,
    kNumber,
    kString,
    kNewline,
};

enum class TokenValueType {
    kInt, 
    kChar, 
    kString,
};

class Token {
 public:
    Token(TokenType type, char val, uint32 lineNum);
    Token(TokenType type, uint64 val, uint32 lineNum);
    Token(TokenType type, std::string val, uint32 lineNum);
    char GetCharTokenVal() const;
    uint64 GetIntTokenVal() const;
    std::string GetStringTokenVal() const;
    TokenType GetTokenType() const;
    TokenValueType GetTokenValueType() const;
 private:
    TokenType type_;
    std::variant<char, uint64, std::string> value_;
    TokenValueType value_type_;
    uint32 token_line_number_;
};


}   // namespace token
}   // namespace frontend
}   // namespace cbit

#endif  // COMPILER_DEV_INC_FRONTEND_TOKEN_HPP_
