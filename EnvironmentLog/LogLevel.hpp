//
// Created by Christoph Rohde on 17.12.23.
//

#pragma once

#include <iostream>
#include <cstdint>

enum class LogLevel : std::uint8_t {
    /// Show all log levels
    DEBUG   = 0b11'111'100,
    /// (Default) Show all log levels except debug
    INFO    = 0b11'111'000,
    /// Show all log levels except debug and info
    WARNING = 0b11'110'000,
    /// Show all log levels except debug, info and warning
    SUCCESS = 0b11'100'000,
    /// Show all log levels except debug, info, warning and success
    ERROR   = 0b11'000'000,
    /// Show only fatal log level
    FATAL   = 0b10'000'000

};

inline std::ostream& operator<<(std::ostream& os, LogLevel const& logLevel){
    switch (logLevel) {
        case LogLevel::DEBUG:
            os << " DEBUG ";
            break;
        case LogLevel::INFO:
            os << " INFO  ";
            break;
        case LogLevel::WARNING:
            os << "WARNING";
            break;
        case LogLevel::SUCCESS:
            os << "SUCCESS";
            break;
        case LogLevel::ERROR:
            os << " ERROR ";
            break;
        case LogLevel::FATAL:
            os << " FATAL ";
            break;
    }
    return os;
}


inline constexpr bool operator==(LogLevel const& lhs, LogLevel const& rhs){
    return static_cast<std::uint8_t>(lhs) == static_cast<std::uint8_t>(rhs);
}

inline constexpr LogLevel operator|(LogLevel const& lhs, LogLevel const& rhs){
    return static_cast<LogLevel>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}

inline constexpr auto operator >= (LogLevel lhs, LogLevel rhs) -> bool {
    return static_cast<std::uint8_t>(lhs) >= static_cast<std::uint8_t>(rhs);
}

inline constexpr auto operator <= (LogLevel lhs, LogLevel rhs) -> bool {
    return static_cast<std::uint8_t>(lhs) <= static_cast<std::uint8_t>(rhs);
}

namespace LogLevelHelper {

    inline constexpr std::string_view getColor(LogLevel const logLevel) {
        switch (logLevel) {
            case LogLevel::DEBUG:
                return "\033[48;2;141;134;201m";
            case LogLevel::INFO:
                return "\033[48;2;57;73;171m";  // INDIGO
            case LogLevel::WARNING:
                return "\033[48;2;190;90;0m";
            case LogLevel::SUCCESS:
                return "\033[48;2;40;170;60m";
            case LogLevel::ERROR:
                return "\033[48;2;180;20;0m";
            case LogLevel::FATAL:
                return "\033[48;2;160;35;20m";
        }
    }

    constexpr std::string_view COLOR_RESET = "\033[0m";
    constexpr std::string_view BOLD = "\033[1m";
    constexpr std::string_view THIN = "\033[2m";
    constexpr std::string_view BORDER = "│";

}
