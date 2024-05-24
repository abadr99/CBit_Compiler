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
// Some useful defines to format 
// 
#define FORMAT_NAME        file_name_ << ":" << line_number_
#define FORMAT_ERROR       RED_COLOR << "Error:" << DEFAULT_COLOR
#define FORMAT_WARNING     YELLOW_COLOR << "Warning:" << DEFAULT_COLOR
#define FORMAT_INFO        BLUE_COLOR << "Info:" << DEFAULT_COLOR
#define OUT                std::cout
#define ENDL               ".\n"

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
                                std::string  msg)
: file_name_(fileName)
, line_number_(lineNumber)
, msg_(msg) {
    /* EMPTY */
}
// =================================== ERROR ===================================
CompilerError::CompilerError(std::string fileName, uint32 lineNumber, std::string msg) 
: CompilerMessage(fileName, lineNumber, msg) {
    /* EMPTY */
}

void CompilerError::Print() {
    OUT << FORMAT_NAME << " " << FORMAT_ERROR << " " << msg_ << ENDL;
}
// =================================== WARNING =================================
CompilerWarning::CompilerWarning(std::string fileName, uint32 lineNumber, std::string msg)
: CompilerMessage(fileName, lineNumber, msg) {
    /* EMPTY */
}

void CompilerWarning::Print() {
    OUT << FORMAT_NAME << " " << FORMAT_WARNING << " " << msg_ << ENDL;
}

// =================================== INFO ====================================
CompilerInfo::CompilerInfo(std::string fileName, uint32 lineNumber, std::string msg)
: CompilerMessage(fileName, lineNumber, msg) {
    /* EMPTY */
}

void CompilerInfo::Print() {
    OUT << FORMAT_NAME << " " << FORMAT_INFO << " " << msg_ << ENDL;
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
