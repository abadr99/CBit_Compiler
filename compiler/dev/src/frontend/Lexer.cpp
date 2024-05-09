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

#include "common/Assert.hpp"
#include "common/Types.hpp"
#include "frontend/Token.hpp"
#include "frontend/Lexer.hpp"

using namespace cbit::frontend::lexer;
using namespace cbit::frontend::token;

Lexer::Lexer(std::string fileName) : fileName_(fileName), stream_(fileName) {
    Lex();
}

typename Lexer::TokenStr_t Lexer::TokenizeLine(std::string line) {
    auto InWordRange = [&](char ch) -> bool {
        return ch >= 'a' && ch <= 'z' ||
               ch >= 'A' && ch <= 'Z' ||
               ch == '_';
    };
    auto IsNumber = [&](char c) -> bool {
        return c >= '0' && c <= '9';  //
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
        return line[i] == '=' && line[i + 1] == '=' // ==
            || line[i] == '!' && line[i + 1] == '=' // !=
            || line[i] == '<' && line[i + 1] == '=' // <=
            || line[i] == '>' && line[i + 1] == '=' // >= 
            || line[i] == '+' && line[i + 1] == '+' // ++
            || line[i] == '-' && line[i + 1] == '-' // --
            || line[i] == '&' && line[i + 1] == '&' // &&
            || line[i] == '|' && line[i + 1] == '|' // ||
            || line[i] == '<' && line[i + 1] == '<' // << 
            || line[i] == '>' && line[i + 1] == '>' // << 
            || line[i] == '+' && line[i + 1] == '=' // +=
            || line[i] == '-' && line[i + 1] == '=' // -=
            || line[i] == '*' && line[i + 1] == '=' // *=
            || line[i] == '/' && line[i + 1] == '=' // /=
            || line[i] == '%' && line[i + 1] == '=' // %=
            || line[i] == '&' && line[i + 1] == '=' // &=
            || line[i] == '|' && line[i + 1] == '=' // |=
            || line[i] == '^' && line[i + 1] == '=' // ^=
            ;
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
        if (IsQuote(line[i])) { // left quote
            word += line[i++];
            while(!IsQuote(line[i])) { // right quote
                word += line[i];
                i++;
            }
            word += "\"";
            i++;
        }
        // ------------------------
        // CONSTRUCT BINARY TOKENS
        if (IsBinaryToken(i)) {
            word = ToString(line[i]) + ToString(line[i + 1]);
            tokenStr.push_back(word);
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

        if (word.size()) { // Avoid pushing empty strings to 'tokenStr'
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
    auto IsKeyWord = [&]() -> bool {
        return token_str == "auto"
            || token_str == "break"
            || token_str == "case"
            || token_str == "char"
            || token_str == "const"
            || token_str == "continue"
            || token_str == "default"
            || token_str == "do"
            || token_str == "double"
            || token_str == "else"
            || token_str == "enum"
            || token_str == "extern"
            || token_str == "float"
            || token_str == "for"
            || token_str == "goto"
            || token_str == "if"
            || token_str == "int"
            || token_str == "long"
            || token_str == "register"
            || token_str == "return"
            || token_str == "short"
            || token_str == "signed"
            || token_str == "sizeof"
            || token_str == "static"
            || token_str == "struct"
            || token_str == "switch"
            || token_str == "typedef"
            || token_str == "union"
            || token_str == "unsigned"
            || token_str == "void"
            || token_str == "volatile"
            || token_str == "while"
            ;
    };
    auto IsOperator = [&]() -> bool {
        return token_str == "+"
            || token_str == "-"
            || token_str == "*"
            || token_str == "/"
            || token_str == "%"
            || token_str == "=="
            || token_str == "!="
            || token_str == ">"
            || token_str == "<"
            || token_str == ">="
            || token_str == "<="
            || token_str == "&&"
            || token_str == "||"
            || token_str == "!"
            || token_str == "&"
            || token_str == "|"
            || token_str == "^"
            || token_str == "~"
            || token_str == "<<"
            || token_str == ">>"
            || token_str == "="
            || token_str == "+="
            || token_str == "-="
            || token_str == "*="
            || token_str == "/="
            || token_str == "%="
            || token_str == "&="
            || token_str == "|="
            || token_str == "^="
            || token_str == "++"
            || token_str == "--"
            || token_str == "."
            || token_str == "->"
            || token_str == "*"
            ;
    };
    auto IsSymbol = [&]() -> bool {
        return token_str == "\""
            || token_str == ")"
            || token_str == "}"
            || token_str == "]" 
            || token_str == ";"
            || token_str == "?"
            || token_str == ":"
            || token_str == "."
            || token_str == ","
            ;
    };
    auto IsString = [&]() -> bool {
        return token_str.front() == '\"' && token_str.back() == '\"';
    };
    enum class NumberMode {
        kNotNumber,
        kHex,
        kDec,
        KBin,
    };
    auto IsNumber = [&]() -> NumberMode {
        // Numbers begin with one of the following:
        // 1) number and remaining is digits from '0' to '9'
        // 2) 0x for hex numbers and remaining is digits from '0' to '9' and 'A' to 'E'
        // 3_ 0b for bin numbers and remaining is digits from '0' to '1'
        std::regex dec_regex("(-?[0-9]+(UL|L|ULL)?)");
        std::regex hex_regex("(0(x|X)[0-9a-fA-F]+)");
        std::regex bin_regex("(0(b|B)[0-1]+)");
        if (std::regex_match(token_str, dec_regex)) {
            return NumberMode::kDec;
        } 
        if (std::regex_match(token_str, hex_regex)) {
            return NumberMode::kHex;
        }
        if (std::regex_match(token_str, bin_regex)) {
            return NumberMode::KBin;
        }
        return NumberMode::kNotNumber;
    };
    auto IsId = [&]() -> bool {
        std::regex id_regex("([a-zA-Z_][a-zA-Z0-9_]*)");
        return std::regex_match(token_str, id_regex);
    };
    if (IsKeyWord()) {
        lexemes_.push_back(Token(TokenType::kKeyword, token_str));
        return;
    }
    if (IsOperator()) {
        lexemes_.push_back(Token(TokenType::kOperator, token_str));
        return;
    }
    if (IsSymbol()) {
        lexemes_.push_back(Token(TokenType::kSymbol, token_str));
        return;
    }
    if (IsString()) {
        lexemes_.push_back(Token(TokenType::kString, token_str));
        return;
    }
    if (IsNumber() != NumberMode::kNotNumber) {
        switch (IsNumber()) {
            case NumberMode::KBin:
                lexemes_.push_back(Token(TokenType::kNumber, std::strtoul(token_str.c_str(), nullptr, 2)));
                break;
            case NumberMode::kDec:
                lexemes_.push_back(Token(TokenType::kNumber, std::strtoul(token_str.c_str(), nullptr, 10)));
                break;
            case NumberMode::kHex:
                lexemes_.push_back(Token(TokenType::kNumber, std::strtoul(token_str.c_str(), nullptr, 16)));
                break;
            default : _UNRERACHABLE;
        }
    }
    if (IsId()) {
        lexemes_.push_back(Token(TokenType::kId, token_str));
        return;
    }
    std::cerr << "[Error]: Unrecognized token found " << token_str << "\n";
    std::abort();
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
