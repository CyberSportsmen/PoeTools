//
// Created by Alex on 05/05/2025.
//

#ifndef POETOOLS_ERROR_HANDLER_H
#define POETOOLS_ERROR_HANDLER_H

#include "Errors.h"
#include <string>
#include <fstream>
#include <mutex>

class ErrorHandler {
public:
    // Initialize log file (call at program start)
    static void initLog(const std::string& filename);

    // Log an error message (to stderr and to log file)
    static void log(const PoeError& err);

    // Helper to catch arbitrary std::exception
    static void handle(const std::exception& e, const std::string& context = "");

    // Shutdown (flush and close log)
    static void shutdown();
private:
    static std::ofstream logFile_;
    static std::mutex     logMutex_;
    ErrorHandler() = delete;
};

#endif // POETOOLS_ERROR_HANDLER_H
