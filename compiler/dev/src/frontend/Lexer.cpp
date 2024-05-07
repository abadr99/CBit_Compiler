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

#include "common/Types.hpp"
#include "frontend/Token.hpp"
#include "frontend/Lexer.hpp"

using namespace cbit::frontend::lexer;
using namespace cbit::frontend::token;

Lexer::Lexer(std::string fileName) : fileName_(fileName), stream_(fileName) {
    Lex();
}

typename Lexer::TokenStr_t Lexer::TokenizeLine(std::string line) {
    auto InWordRange = [&](char ch)->bool {
        return ch >= 'a' && ch <= 'z' ||
               ch >= 'A' && ch <= 'Z' ||
               ch == '_';
    };
    
    auto IsComment = [&](uint32 i)->bool {
        return line[i] == '/' && line[i + 1] == '/';
    };

    auto IsSpace = [&](char c) -> bool {
        return c == ' ';
    };
    auto IsQuote = [&](char c)->bool {
        return c == '\"';
    };

    typename Lexer::TokenStr_t tokenStr;
    std::string word;

    // Iterate over line character by character
    for (uint32 i = 0 ; i < line.size(); ++i) {
        // ------------------------------------------------- 
        // IN CASE OF SINGLE COMMENT JUST IGNORE THE COMMENT
        if (IsComment(i)) {
            break;
        }
        // ----------------------------------------- 
        // IGNORE SPACES AS WE DON'T CARE ABOUT THEM 
        if (IsSpace(line[i])) {
            continue;
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
            tokenStr.push_back(word);
            word = "";
            i++;
        }
        // --------------------------------------------------------------
        // IF WE HAVE WORD THAT IS NOT OPERATOR OR SPECIAL CHARACTER THEN 
        // CONSTRUCT 'word' VARIABLE
        while (InWordRange(line[i])) {
            word += line[i];
            i++;
        }
        if (word.size()) { // Avoid pushing empty strings to 'tokenStr'
            tokenStr.push_back(word);
        }
        word = "";

        // ----------------------------------------------
        // OTHERWISE PUSH CURRENT CHARACTER TO 'tokenStr'
        tokenStr.push_back(std::string(sizeof(char),line[i]));
    }
    return tokenStr;
}

void Lexer::AddLexeme(Token token) {

}

void Lexer::Lex() {
    if (!stream_.is_open()) {
        std::cerr << "Can't open " << fileName_ << "\n";
	    std::abort();
    }
    // Loop over files and begin lexing each line
    std::string currentLine;
    while (std::getline(stream_, currentLine)) {

	}
}
