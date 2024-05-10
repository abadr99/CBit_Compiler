/**
 * @file Token.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string>
#include "common/Assert.hpp"
#include "common/Types.hpp"
#include "frontend/Token.hpp"

using namespace cbit::frontend::token;

Token::Token(TokenType type, char val): type_(type), 
                                        value_(val), 
                                        value_type_(TokenValueType::kChar)
{ /* EMPTY */ }

Token::Token(TokenType type, uint64 val): type_(type), 
                                          value_(val), 
                                          value_type_(TokenValueType::kInt)
{ /* EMPTY */ }

Token::Token(TokenType type, std::string val): type_(type), 
                                               value_(val), 
                                               value_type_(TokenValueType::kString)
{ /* EMPTY */ }


char Token::GetCharTokenVal() const {
    CBIT_ASSERT(std::holds_alternative<char>(value_), 
               "Calling GetCharTokenVal() with non char value type\n");
    return std::get<char>(value_);
}

uint64 Token::GetIntTokenVal() const {
    CBIT_ASSERT(std::holds_alternative<uint64>(value_), 
                "Calling GetIntTokenVal() with non uint64 value type\n");
    return std::get<uint64>(value_);
}

std::string Token::GetStringTokenVal() const {
    CBIT_ASSERT(std::holds_alternative<std::string>(value_), 
                "Calling GetStringTokenVal() with non string value type\n");
    return std::get<std::string>(value_);
}

TokenType Token::GetTokenType() const {
    return type_;
}

TokenValueType Token::GetTokenValueType() const {
    return value_type_;
}