/**
 * @file lexer.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>

#include "common/Assert.hpp"
#include "common/Types.hpp"
#include "frontend/Token.hpp"
#include "frontend/Lexer.hpp"

using namespace cbit::frontend::lexer;
using namespace cbit::frontend::token;

// Look-up table to represent each known token with its type
static const std::unordered_set<std::string> binaryTokens = {
    "==",
    "!=",
    "<=",
    ">=",
    "++",
    "--",
    "&&",
    "||",
    "<<",
    "<<",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^=",
};
// Look-up table to represent each known token with its type
static const std::unordered_map<std::string, TokenType> knownTokens = {
    {"auto",     TokenType::kKeyword},
    {"break",    TokenType::kKeyword},
    {"case",     TokenType::kKeyword},
    {"char",     TokenType::kKeyword},
    {"const",    TokenType::kKeyword},
    {"continue", TokenType::kKeyword},
    {"default",  TokenType::kKeyword},
    {"do",       TokenType::kKeyword},
    {"double",   TokenType::kKeyword},
    {"else",     TokenType::kKeyword},
    {"enum",     TokenType::kKeyword},
    {"extern",   TokenType::kKeyword},
    {"float",    TokenType::kKeyword},
    {"for",      TokenType::kKeyword},
    {"goto",     TokenType::kKeyword},
    {"if",       TokenType::kKeyword},
    {"int",      TokenType::kKeyword},
    {"long",     TokenType::kKeyword},
    {"register", TokenType::kKeyword},
    {"return",   TokenType::kKeyword},
    {"short",    TokenType::kKeyword},
    {"signed",   TokenType::kKeyword},
    {"sizeof",   TokenType::kKeyword},
    {"static",   TokenType::kKeyword},
    {"struct",   TokenType::kKeyword},
    {"switch",   TokenType::kKeyword},
    {"typedef",  TokenType::kKeyword},
    {"union",    TokenType::kKeyword},
    {"unsigned", TokenType::kKeyword},
    {"void",     TokenType::kKeyword},
    {"volatile", TokenType::kKeyword},
    {"while",    TokenType::kKeyword},
    {"+",        TokenType::kOperator},
    {"-",        TokenType::kOperator},
    {"*",        TokenType::kOperator},
    {"/",        TokenType::kOperator},
    {"%",        TokenType::kOperator},
    {"==",       TokenType::kOperator},
    {"!=",       TokenType::kOperator},
    {">",        TokenType::kOperator},
    {"<",        TokenType::kOperator},
    {">=",       TokenType::kOperator},
    {"<=",       TokenType::kOperator},
    {"&&",       TokenType::kOperator},
    {"||",       TokenType::kOperator},
    {"!",        TokenType::kOperator},
    {"&",        TokenType::kOperator},
    {"|",        TokenType::kOperator},
    {"^",        TokenType::kOperator},
    {"~",        TokenType::kOperator},
    {"<<",       TokenType::kOperator},
    {">>",       TokenType::kOperator},
    {"=",        TokenType::kOperator},
    {"+=",       TokenType::kOperator},
    {"-=",       TokenType::kOperator},
    {"*=",       TokenType::kOperator},
    {"/=",       TokenType::kOperator},
    {"%=",       TokenType::kOperator},
    {"&=",       TokenType::kOperator},
    {"|=",       TokenType::kOperator},
    {"^=",       TokenType::kOperator},
    {"++",       TokenType::kOperator},
    {"--",       TokenType::kOperator},
    {".",        TokenType::kOperator},
    {"->",       TokenType::kOperator},
    {"*",        TokenType::kOperator},
    {"(",        TokenType::kOperator},
    {"[",        TokenType::kOperator},
    {"{",        TokenType::kOperator},
    {"\"",       TokenType::kSymbol},
    {")",        TokenType::kSymbol},
    {"}",        TokenType::kSymbol},
    {"]",        TokenType::kSymbol},
    {";",        TokenType::kSymbol},
    {"?",        TokenType::kSymbol},
    {":",        TokenType::kSymbol},
    {".",        TokenType::kSymbol},
    {",",        TokenType::kSymbol}
};

Lexer::Lexer(std::string fileName) : fileName_(fileName), stream_(fileName) {
    Lex();
}

typename Lexer::TokenStr_t Lexer::TokenizeLine(std::string line) {
    auto InWordRange = [&](char ch) -> bool {
        return (ch >= 'a' && ch <= 'z')
            || (ch >= 'A' && ch <= 'Z')
            || (ch == '_');
    };
    auto IsNumber = [&](char c) -> bool {
        return c >= '0' && c <= '9';
    };
    auto IsComment = [&](uint32 i) -> bool {
        return line[i] == '/' && line[i + 1] == '/';
    };
    auto IsSpace = [&](char c) -> bool {
        return c == ' ';
    };
    auto IsQuote = [&](char c) -> bool {
        return c == '\"';
    };
    auto IsBinaryToken = [&](uint32 i) -> bool {
        return binaryTokens.count(line.substr(i, 2));
    };
    auto ToString = [&](char c) -> std::string {
        return std::string(sizeof(char), c);
    };

    typename Lexer::TokenStr_t tokenStr;
    std::string word;

    // Iterate over line character by character
    for (uint32 i = 0 ; i < line.size(); ++i) {
        // --------------------------------------------------------
        // IN CASE OF SINGLE COMMENT JUST IGNORE THE REMAINING LINE
        if (IsComment(i)) {
            break;
        }
        // ----------------------------------------- 
        // CONSTRUCT THE WHOLE STRING BETWEEN QUOTES
        if (IsQuote(line[i])) {     // left quote
            word += line[i++];
            while (!IsQuote(line[i])) {  // right quote
                word += line[i];
                i++;
            }
            word += "\"";
            i++;
        }
        // ------------------------
        // CONSTRUCT BINARY TOKENS
        if (IsBinaryToken(i)) {
            tokenStr.push_back(line.substr(i, 2));
            word = "";
            i++;  // skip next character
            continue;
        }
        // --------------------------------------------------------------
        // IF WE HAVE WORD THAT IS NOT OPERATOR OR SPECIAL CHARACTER THEN 
        // CONSTRUCT 'word' VARIABLE
        while (InWordRange(line[i])) {
            word += line[i];
            i++;
        }
        // -----------------
        // CONSTRUCT NUMBERS
        while (IsNumber(line[i])) {
            word += line[i];
            i++;
        }

        if (word.size()) {  // Avoid pushing empty strings to 'tokenStr'
            tokenStr.push_back(word);
            word = "";
        }
        // ----------------------------------------- 
        // IGNORE SPACES AS WE DON'T CARE ABOUT THEM 
        if (IsSpace(line[i])) {
            continue;
        }
        // ----------------------------------------------
        // OTHERWISE PUSH CURRENT CHARACTER TO 'tokenStr'
        tokenStr.push_back(ToString(line[i]));
    }
    return tokenStr;
}

void Lexer::AddLexeme(std::string token_str) {    
    auto IsString = [&]() -> bool {
        static const std::regex str_regex("\".*\"");
        return std::regex_match(token_str, str_regex);;
    };
    auto IsNumber = [&]() -> bool {
        // Numbers begin with one of the following:
        // 1) number and remaining is digits from '0' to '9'
        // 2) 0x for hex numbers and remaining is digits from '0' to '9' and 'A' to 'E'
        // 3_ 0b for bin numbers and remaining is digits from '0' to '1'
        static const std::regex dec_regex("(-?[0-9]+(UL|L|ULL)?)");
        static const std::regex hex_regex("(0(x|X)[0-9a-fA-F]+)");
        static const std::regex bin_regex("(0(b|B)[0-1]+)");
        return std::regex_match(token_str, dec_regex) || 
               std::regex_match(token_str, hex_regex) ||
               std::regex_match(token_str, bin_regex);
    };
    auto IsId = [&]() -> bool {
        std::regex id_regex("([a-zA-Z_][a-zA-Z0-9_]*)");
        return std::regex_match(token_str, id_regex);
    };
    // --- BEGIN WITH KNOWN TOKENS 
    if (knownTokens.count(token_str)) {
        lexemes_.push_back(Token(knownTokens.at(token_str), token_str));
        return;
    }
    // --- STRING TOKENS
    if (IsString()) {
        lexemes_.push_back(Token(TokenType::kString, token_str));
        return;
    }
    // --- NUMBER TOKENS
    if (IsNumber()) {
        uint64 value;
        if (token_str.substr(0, 2) == "0x" || token_str.substr(0, 2) == "0X") {
            std::sscanf(token_str.c_str(), "%lx", &value);
        } else if (token_str.substr(0, 2) == "0b" || token_str.substr(0, 2) == "0B") {
            std::sscanf(token_str.c_str(), "%li", &value);
        } else {
            std::sscanf(token_str.c_str(), "%ld", &value);
        }
        lexemes_.push_back(Token(TokenType::kNumber, value));
        return;
    }
    // --- ID TOKENS
    if (IsId()) {
        lexemes_.push_back(Token(TokenType::kId, token_str));
        return;
    }
    std::cerr << "[Error]: Unrecognized token found " << token_str << "\n";
    //std::abort();
}

void Lexer::Lex() {
    if (!stream_.is_open()) { 
        std::cerr << "Can't open " << fileName_ << "\n";
        std::abort();
    }
    // Loop over files and begin lexing each line
    std::string currentLine;
    while (std::getline(stream_, currentLine)) {
        auto tokens = TokenizeLine(currentLine);
        for (auto& token : tokens) {
            AddLexeme(token);
        }
    }
}

typename Lexer::Tokens_t Lexer::Get() const {
    return lexemes_;
}