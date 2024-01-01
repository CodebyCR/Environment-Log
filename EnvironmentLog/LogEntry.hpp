//
// Created by Christoph Rohde on 19.12.23.
//

#pragma once

#include "LogLevel.hpp"

#include <iostream>
#include <string_view>
#include <source_location>

struct LogEntry{
public:
    LogLevel logLevel;
    std::string_view message;
    std::optional<std::source_location> location;
};


