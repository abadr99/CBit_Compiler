/**
 * @file CompilerReporter.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <memory>
#include <utility>
#include <iostream>
#include <string>

#include "common/Globals.hpp"
#include "common/Assert.hpp"
#include "common/Types.hpp"
#include "common/CompilerReporter.hpp"

// -----------------------------------------------------------------------------
// NAMESPACES 
// 
using namespace cbit::common::compiler_reporter;

// -----------------------------------------------------------------------------
// CompilerMessage Class Family Definitions
//
// =================================== BASE ===================================
CompilerMessage::CompilerMessage(std::string fileName, 
                                uint32       lineNumber, 
                                std::string  msg,
                                std::string  color)
: file_name_(fileName)
, line_number_(lineNumber)
, msg_(msg)
, color_(color) {
    /* EMPTY */
}
// =================================== ERROR ===================================
CompilerError::CompilerError(std::string fileName, uint32 lineNumber, std::string msg) 
: CompilerMessage(fileName, lineNumber, msg, RED_COLOR) {
    /* EMPTY */
}

void CompilerError::Print() {
    std::cout << color_ << "Error: " << DEFAULT_COLOR << msg_ << ":" << line_number_ << ".\n";
}
// =================================== WARNING =================================
CompilerWarning::CompilerWarning(std::string fileName, uint32 lineNumber, std::string msg)
: CompilerMessage(fileName, lineNumber, msg, YELLOW_COLOR) {
    /* EMPTY */
}

void CompilerWarning::Print() {
    std::cout << color_ << "Warning: " << DEFAULT_COLOR << msg_ << ":" << line_number_ << ".\n";
}

// =================================== INFO ====================================
CompilerInfo::CompilerInfo(std::string fileName, uint32 lineNumber, std::string msg)
: CompilerMessage(fileName, lineNumber, msg, BLUE_COLOR) {
    /* EMPTY */
}

void CompilerInfo::Print() {
    std::cout << color_ << "Info: " << DEFAULT_COLOR << msg_ << ".\n";
}

// -----------------------------------------------------------------------------
// Compiler Reporter Implementations
// 
CompilerReporter* CompilerReporter::pCompilerReporter = nullptr;
CompilerReporter& CompilerReporter::Get() {
    if (pCompilerReporter == nullptr) {
        pCompilerReporter = new CompilerReporter();
    } 
    return *pCompilerReporter;
}

void CompilerReporter::Add(std::unique_ptr<CompilerMessage> cm) {
    messages_.push_back(std::move(cm));
}

const typename CompilerReporter::message_t& CompilerReporter::GetMessages() const {
    return messages_;
}

void CompilerReporter::Report() const {
    for (auto& msg : messages_) {
        msg->Print();
    }
}

// -----------------------------------------------------------------------------
// Compiler Abort implementations
// 
void CompilerAbort::Abort(std::string fileName, std::string msg) {
    std::cerr << fileName << ":" << msg << "\n";
    std::abort();
}
