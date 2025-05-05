//
// Created by Alex on 05/05/2025.
//

#include "../include/ErrorHandler.h"
#include <iostream>
#include <ctime>

std::ofstream ErrorHandler::logFile_;
std::mutex     ErrorHandler::logMutex_;

void ErrorHandler::initLog(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex_);
    logFile_.open(filename, std::ios::out | std::ios::app);
    if (!logFile_) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

void ErrorHandler::log(const PoeError& err) {
    std::lock_guard<std::mutex> lock(logMutex_);
    // Timestamp
    std::time_t t = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

    // Formatted message
    std::string line = "[" + std::string(buf) + "] " + err.what();

    // Console
    std::cerr << line << std::endl;

    // File
    if (logFile_) {
        logFile_ << line << std::endl;
    }
}

void ErrorHandler::handle(const std::exception& e, const std::string& context) {
    // Wrap any non-PoeError
    if (const PoeError* pe = dynamic_cast<const PoeError*>(&e)) {
        log(*pe);
    } else {
        PoeError wrapper("Unhandled exception" + (context.empty() ? "" : " in " + context) + ": " + e.what());
        log(wrapper);
    }
}

void ErrorHandler::shutdown() {
    std::lock_guard<std::mutex> lock(logMutex_);
    if (logFile_) {
        logFile_.flush();
        logFile_.close();
    }
}
