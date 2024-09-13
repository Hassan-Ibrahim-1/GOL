#include <iostream>

#include "error_handler.hpp"

bool ErrorHandler::had_error = false;

void ErrorHandler::error(const std::string& message) {
    report(message);
    had_error = true;
}

void ErrorHandler::report(const std::string& message) {
    std::cerr << "\033[1;31m[ERROR]\033[0m: " << message << '\n';
}

