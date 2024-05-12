/**
 * @file Assert.hpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMPILER_DEV_INC_COMMON_ASSERT_HPP_
#define COMPILER_DEV_INC_COMMON_ASSERT_HPP_

#include <assert.h>
#include <iostream>
#include <cstdlib>


#define CBIT_ASSERT(expr, msg)\
    assert(expr);\
    if (!expr) std::cerr << msg;

#define _UNREACHABLE\
    std::cerr << "[UNREACHABLE]: Unreachable code detected in " << __FILE__ << __LINE__ << "\n";\
    std::abort();

#define _UNIMPLEMENTED\
    std::cerr << "[UNIMPLEMENTED]: Unimplemented feature " << __FILE__ << __LINE__;\
    std::abort();
#endif  // COMPILER_DEV_INC_COMMON_ASSERT_HPP_
