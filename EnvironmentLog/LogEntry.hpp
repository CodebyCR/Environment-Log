//
// Created by Christoph Rohde on 19.12.23.
//

#pragma once

#include "LogLevel.hpp"

#include <chrono>

struct LogEntry{
public:
    LogLevel logLevel;
    std::string_view message;
};

inline auto operator<<(std::ostream &stream, const LogEntry &logEntry) -> std::ostream & {
    stream << logEntry.message;
    return stream;
}
