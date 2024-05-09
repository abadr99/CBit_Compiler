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
    Token(TokenType type, char val);
    Token(TokenType type, uint64 val);
    Token(TokenType type, std::string val);
    char GetCharTokenVal() const;
    uint64 GetIntTokenVal() const;
    std::string GetStringTokenVal() const;
 private:
    TokenType type_;
    std::variant<char, uint64, std::string> value_;
    TokenValueType value_type_;
};


}   // namespace token
}   // namespace frontend
}   // namespace cbit

#endif  // COMPILER_DEV_INC_FRONTEND_TOKEN_HPP_
