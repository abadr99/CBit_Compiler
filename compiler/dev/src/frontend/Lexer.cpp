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

#include <fstream>
#include "frontend/Token.hpp"
#include "frontend/Lexer.hpp"

using namespace cbit::frontend::lexer;
using namespace cbit::frontend::token;

Lexer::Lexer(std::string fileName) : fileName_(fileName) {
    Lex();
}

void Lexer::Lex() {

}
