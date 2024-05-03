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

#define CBIT_ASSERT(expr, msg)\
    assert(expr);\
    std::cerr << msg;

#endif  // COMPILER_DEV_INC_COMMON_ASSERT_HPP_
