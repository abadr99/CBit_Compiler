#include <gtest/gtest.h>
#include <filesystem>
#include <string>

#include "common/Assert.hpp"
#include "common/Types.hpp"
#include "frontend/Lexer.hpp"

using namespace cbit::frontend::lexer;
using namespace cbit::frontend::token;

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

template<typename T>
static void TestToken(Token t, T expectedVal, TokenType type) {
    _UNREACHABLE;
}

template<>
void TestToken<std::string>(Token t, std::string expectedVal, TokenType type) {
    EXPECT_EQ(t.GetStringTokenVal(), expectedVal);
    EXPECT_EQ(t.GetTokenType(), type);
}

template<>
void TestToken<uint64>(Token t, uint64 expectedVal, TokenType type) {
    EXPECT_EQ(t.GetIntTokenVal(), expectedVal);
    EXPECT_EQ(t.GetTokenType(), type);
}


void TestKnownToken(Token t, std::string expectedVal) {
    EXPECT_EQ(t.GetStringTokenVal(), expectedVal);
    EXPECT_EQ(t.GetTokenType(), knownTokens.at(expectedVal));
}

TEST(Lexer, test1) {
    std::filesystem::path currentPath = __FILE__;
    std::filesystem::path parentDirectory = currentPath.parent_path();
    std::string input_dir = parentDirectory.c_str() + std::string("/input-test-cases/input1.in");

    Lexer lex(input_dir);
    auto lexerOutput = lex.Get();
    
    int i = 0;
    // int main() {
    TestKnownToken(lexerOutput[i++], "int");
    TestToken<std::string>(lexerOutput[i++], "main", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "("); 
    TestKnownToken(lexerOutput[i++], ")");
    TestKnownToken(lexerOutput[i++], "{");
    
    // int n, i;
    TestKnownToken(lexerOutput[i++], "int");
    TestToken<std::string>(lexerOutput[i++], "n", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ",");
    TestToken<std::string>(lexerOutput[i++], "i", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ";");
    
    // unsigned long long fact = 1;
    TestKnownToken(lexerOutput[i++], "unsigned");
    TestKnownToken(lexerOutput[i++], "long");
    TestKnownToken(lexerOutput[i++], "long");
    TestToken<std::string>(lexerOutput[i++], "fact", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "=");
    TestToken<uint64>(lexerOutput[i++], 1, TokenType::kNumber);
    TestKnownToken(lexerOutput[i++], ";");
    
    // printf("Enter an integer: ");
    TestToken<std::string>(lexerOutput[i++], "printf", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "(");
    TestToken<std::string>(lexerOutput[i++], "\"Enter an integer: \"", TokenType::kString);
    TestKnownToken(lexerOutput[i++], ")");
    TestKnownToken(lexerOutput[i++], ";");
    
    // scanf("%d", &n);
    TestToken<std::string>(lexerOutput[i++], "scanf", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "(");
    TestToken<std::string>(lexerOutput[i++], "\"%d\"", TokenType::kString);
    TestKnownToken(lexerOutput[i++], ",");
    TestKnownToken(lexerOutput[i++], "&");
    TestToken<std::string>(lexerOutput[i++], "n", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ")");
    TestKnownToken(lexerOutput[i++], ";");
    
    // if (n < 0)
    TestKnownToken(lexerOutput[i++], "if");
    TestKnownToken(lexerOutput[i++], "(");
    TestToken<std::string>(lexerOutput[i++], "n", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "<");
    TestToken<uint64>(lexerOutput[i++], 0ULL, TokenType::kNumber);
    TestKnownToken(lexerOutput[i++], ")");
    
    // printf("Error! Factorial of a negative number doesn't exist. :(");
    TestToken<std::string>(lexerOutput[i++], "printf", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "(");
    TestToken<std::string>(lexerOutput[i++], "\"Error! Factorial of a negative number doesn't exist. :(\"", TokenType::kString);
    TestKnownToken(lexerOutput[i++], ")");
    TestKnownToken(lexerOutput[i++], ";");

    // else {
    TestKnownToken(lexerOutput[i++], "else");
    TestKnownToken(lexerOutput[i++], "{");

    // for (i = 1; i <= n; ++i) {
    TestKnownToken(lexerOutput[i++], "for");
    TestKnownToken(lexerOutput[i++], "(");
    TestToken<std::string>(lexerOutput[i++], "i", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "=");
    TestToken<uint64>(lexerOutput[i++], 1ULL, TokenType::kNumber);
    TestKnownToken(lexerOutput[i++], ";");
    TestToken<std::string>(lexerOutput[i++], "i", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "<=");
    TestToken<std::string>(lexerOutput[i++], "n", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ";");
    TestKnownToken(lexerOutput[i++], "++");
    TestToken<std::string>(lexerOutput[i++], "i", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ")");
    TestKnownToken(lexerOutput[i++], "{");

    // fact *= i;
    TestToken<std::string>(lexerOutput[i++], "fact", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "*=");
    TestToken<std::string>(lexerOutput[i++], "i", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ";");

    // }
    TestKnownToken(lexerOutput[i++], "}");

    // printf("Factorial of %d = %llu", n, fact);
    TestToken<std::string>(lexerOutput[i++], "printf", TokenType::kId);
    TestKnownToken(lexerOutput[i++], "(");
    TestToken<std::string>(lexerOutput[i++], "\"Factorial of %d = %llu\"", TokenType::kString);
    TestKnownToken(lexerOutput[i++], ",");
    TestToken<std::string>(lexerOutput[i++], "n", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ",");
    TestToken<std::string>(lexerOutput[i++], "fact", TokenType::kId);
    TestKnownToken(lexerOutput[i++], ")");
    TestKnownToken(lexerOutput[i++], ";");

    // }
    TestKnownToken(lexerOutput[i++], "}");

    // return 0;
    TestKnownToken(lexerOutput[i++], "return");
    TestToken<uint64>(lexerOutput[i++], 0ULL, TokenType::kNumber);
    TestKnownToken(lexerOutput[i++], ";");

    // }
    TestKnownToken(lexerOutput[i++], "}");
}
