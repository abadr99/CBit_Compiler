/**
 * @file Utils.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMPILER_DEV_INC_COMMON_UTILS_HPP_
#define COMPILER_DEV_INC_COMMON_UTILS_HPP_

#include <string>
#include "common/Types.hpp"

#define STRING_TERMINATOR   ('\0')
#define BINARY              (2)
#define HEX                 (16)

namespace cbit {
namespace common {
namespace utils  {
namespace strings {

template<typename T>
bool ConvertBinaryStringToInt(const std::string& binary_string, T* out) {
    // First check if the string is valid or not
    for (auto& digit : binary_string) {
        if (digit == '1')  continue;
        if (digit == '0')  continue;
        return false;   // Not a binary number  
    }
    *out = std::stoi(binary_string, nullptr, BINARY);
    return true; 
}

template<typename T>
bool ConvertHexStringToInt(const std::string& hex_string, T* out) {
    // First check if the string is valid or not
    for (auto& digit : hex_string) {
        if (digit >= '0' || digit <= '9')  continue;
        if (digit >= 'A' || digit <= 'F')  continue;
        if (digit >= 'a' || digit <= 'f')  continue;
        return false;   // Not a hex number  
    }
    *out = std::stoi(hex_string, nullptr, HEX);
    return true; 
}

}   // namespace strings
}   // namespace utils
}   // namespace common
}   // namespace cbit

#endif  // COMPILER_DEV_INC_COMMON_UTILS_HPP_
