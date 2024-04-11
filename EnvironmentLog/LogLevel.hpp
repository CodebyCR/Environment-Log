//
// Created by Christoph Rohde on 17.12.23.
//

#pragma once

#include <iostream>
#include <cstdint>

enum class LogLevel: std::uint8_t {
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
        using enum LogLevel;
        case DEBUG:
            os << "DEBUG  ";
            break;
        case INFO:
            os << "INFO   ";
            break;
        case WARNING:
            os << "WARNING";
            break;
        case SUCCESS:
            os << "SUCCESS";
            break;
        case ERROR:
            os << "ERROR  ";
            break;
        case FATAL:
            os << "FATAL  ";
            break;
    }
    return os;
}


inline constexpr bool operator==(LogLevel const& lhs, LogLevel const& rhs){
    return static_cast<std::byte>(lhs) == static_cast<std::byte>(rhs);
}

inline constexpr LogLevel operator|(LogLevel const& lhs, LogLevel const& rhs){
    return static_cast<LogLevel>(static_cast<std::byte>(lhs) | static_cast<std::byte>(rhs));
}

inline constexpr auto operator >= (LogLevel lhs, LogLevel rhs) -> bool {
    return static_cast<std::byte>(lhs) >= static_cast<std::byte>(rhs);
}

inline constexpr auto operator <= (LogLevel lhs, LogLevel rhs) -> bool {
    return static_cast<std::byte>(lhs) <= static_cast<std::byte>(rhs);
}

namespace LogLevelHelper {

    inline constexpr std::string_view getColor(LogLevel const logLevel) {
        switch (logLevel) {
            using enum LogLevel;
            case DEBUG:
                return "\033[38;2;141;134;201m";
            case INFO:
                return "\033[38;2;77;83;171m";  // INDIGO
            case WARNING:
                return "\033[38;2;190;90;0m";
            case SUCCESS:
                return "\033[38;2;40;170;60m";
            case ERROR:
                return "\033[38;2;180;20;0m";
            case FATAL:
                return "\x1B[38;2;160;35;20m";
        }

        return "\033[0m";
    }

    constexpr std::string_view COLOR_RESET = "\033[0m";
    constexpr std::string_view BOLD = "\033[1m";
    constexpr std::string_view THIN = "\033[2m";
    constexpr std::string_view BORDER = "│";

}
