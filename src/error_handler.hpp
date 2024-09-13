#pragma once

#include <string>

namespace ErrorHandler {

extern bool had_error;

void error(const std::string& message);
void report(const std::string& message);

}

