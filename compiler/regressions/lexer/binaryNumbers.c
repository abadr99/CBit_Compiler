// RUN: cbit %s --keep_lexer=true 
// RUN: FileCheck %s -input-file binaryNumbers.lex
// CHECK: 42                                                                              Number
// RUN: rm -rf binaryNumbers.lex

// Define binary numbers as variables
binary1 = 0b101010;  // Binary representation of decimal 42
binary2 = 0b110011;  // Binary representation of decimal 51
