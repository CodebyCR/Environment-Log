//
// Created by Christoph Rohde on 17.12.23.
//

#pragma once

#include "LogLevel.hpp"
#include "LogEntry.hpp"

#include <iostream>

class LogStream {
private:
    bool colorize;
    LogLevel displayedLogLevel;
    std::ostream &stream;


    LogStream(bool colorize, LogLevel displayedLogLevel, std::ostream &stream = std::cout):
            colorize(colorize),
            displayedLogLevel(displayedLogLevel),
            stream(stream)  {}

    /// LogLevel filter
    inline auto logLevelFilter(LogLevel logLevel) -> bool {
        return logLevel <= displayedLogLevel;
    }

    /// Colorize


public:

    /// Singleton
    static auto create(const bool colorize = true,
                       const LogLevel displayedLogLevel = LogLevel::INFO,
                       std::ostream &stream = std::cout) -> LogStream& {
        static LogStream logStream = LogStream(colorize, displayedLogLevel, stream);
        return logStream;
    }

    template<typename T>
    auto operator<<(T const &t) -> LogStream & {
        stream << t;
        return *this;
    }

    auto operator<<(std::ostream &(*f)(std::ostream &)) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(std::ios &(*f)(std::ios &)) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(std::ios_base &(*f)(std::ios_base &)) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(std::string_view s) -> LogStream & {
        stream << s;
        return *this;
    }

    auto operator<<(std::string const &s) -> LogStream & {
        stream << s;
        return *this;
    }

    auto operator<<(char const *s) -> LogStream & {
        stream << s;
        return *this;
    }

    auto operator<<(char c) -> LogStream & {
        stream << c;
        return *this;
    }

    auto operator<<(int i) -> LogStream & {
        stream << i;
        return *this;
    }

    auto operator<<(unsigned int i) -> LogStream & {
        stream << i;
        return *this;
    }

    auto operator<<(long i) -> LogStream & {
        stream << i;
        return *this;
    }

    auto operator<<(unsigned long i) -> LogStream & {
        stream << i;
        return *this;
    }

    auto operator<<(long long i) -> LogStream & {
        stream << i;
        return *this;
    }

    auto operator<<(unsigned long long i) -> LogStream & {
        stream << i;
        return *this;
    }

    auto operator<<(float f) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(double f) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(long double f) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(LogLevel const logLevel) -> LogStream & {
//        if (logLevelFilter(logLevel)) {
            stream << logLevel;
//        }
        return *this;
    }

    auto operator << (LogEntry const& logEntry) -> std::ostream & {
        bool logFilterFit = logLevelFilter(logEntry.logLevel);

        if(logFilterFit){
            // TODO: Colorize ???
            stream  << logEntry.message;
        }
        return stream;
    }
};
