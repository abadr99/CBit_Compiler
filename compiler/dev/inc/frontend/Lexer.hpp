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

// As token is type and value, Actually we have different types of values 
// int, char and strings. In order to achieve map that takes different types of
// values then we have to use the following approach.
// See: https://stackoverflow.com/questions/24702235/c-stdmap-holding-any-type-of-value
//      https://godbolt.org/z/Wo8WenMcn

struct BaseTokenValue {
    BaseTokenValue()  = default;
    ~BaseTokenValue() = default;
};

template<typename T>
struct TokenValue: public BaseTokenValue {
    TokenValue(T value);
    T value;
};

class Lexer {
 public:
    using TokenStream_t = std::map<TokenTypes, BaseTokenValue>;
    Lexer(std::string fileName);
    TokenStream_t GetTokens() const;
 private:
    using TokenPair_t   = std::pair<TokenTypes, BaseTokenValue&>;
    using CharToken_t   = TokenValue<char>;
    using StringToken_t = TokenValue<std::string>;
    using IntToken_t    = TokenValue<int>;

    std::string fileName_;
    TokenStream_t tokens_;
};

}  // namespace lexer
}  // namespace common
}  // namespace cbit