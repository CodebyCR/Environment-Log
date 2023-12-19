//
// Created by Christoph Rohde on 17.12.23.
//

#pragma once

#include <iostream>

enum class LogLevel : std::uint8_t {
    /// Show all log levels
    DEBUG   = 0b11111,
    /// (Default) Show all log levels except debug
    INFO    = 0b11110,
    /// Show all log levels except debug and info
    WARNING = 0b11100,
    /// Show all log levels except debug, info and warning
    ERROR   = 0b11000,
    /// Show only fatal log level
    FATAL   = 0b10000

};

inline std::ostream& operator<<(std::ostream& os, LogLevel const& logLevel){
    switch (logLevel) {
        case LogLevel::DEBUG:
            os << "DEBUG";
            break;
        case LogLevel::INFO:
            os << "INFO";
            break;
        case LogLevel::WARNING:
            os << "WARNING";
            break;
        case LogLevel::ERROR:
            os << "ERROR";
            break;
        case LogLevel::FATAL:
            os << "FATAL";
            break;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, LogLevel& logLevel){
    std::string logLevelString;
    is >> logLevelString;
    if (logLevelString == "DEBUG") {
        logLevel = LogLevel::DEBUG;
    } else if (logLevelString == "INFO") {
        logLevel = LogLevel::INFO;
    } else if (logLevelString == "WARNING") {
        logLevel = LogLevel::WARNING;
    } else if (logLevelString == "ERROR") {
        logLevel = LogLevel::ERROR;
    } else if (logLevelString == "FATAL") {
        logLevel = LogLevel::FATAL;
    } else {
        is.setstate(std::ios_base::failbit);
    }

    return is;
}

inline constexpr bool operator==(LogLevel const& lhs, LogLevel const& rhs){
    return static_cast<std::uint8_t>(lhs) == static_cast<std::uint8_t>(rhs);
}

inline constexpr LogLevel operator|(LogLevel const& lhs, LogLevel const& rhs){
    return static_cast<LogLevel>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}

inline constexpr std::string_view getColor(LogLevel const logLevel){
    switch (logLevel) {
        case LogLevel::DEBUG:
            return "\033[0;37m";
        case LogLevel::INFO:
            return "\033[0;32m";
        case LogLevel::WARNING:
            return "\033[0;33m";
        case LogLevel::ERROR:
            return "\033[0;31m";
        case LogLevel::FATAL:
            return "\033[0;35m";
    }
}


