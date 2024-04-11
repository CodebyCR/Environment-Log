//
// Created by Christoph Rohde on 17.12.23.
//

#pragma once

#include "LogLevel.hpp"
#include "LogEntry.hpp"
#include "EnvConfig.hpp"

#include <iostream>
#include <fstream>
#include <utility>
#include <format>

class LogStream {
private:
    EnvConfig envConfig;
    std::ostream &stream;


    explicit LogStream(EnvConfig const& envConfig):
            envConfig(envConfig),
            stream(envConfig.stream)  {}

    LogStream(EnvConfig envConfig, std::ostream & ofstream):
            envConfig(std::move(envConfig)),
            stream(ofstream){}

    /// LogLevel filter
    [[nodiscard]] inline auto logLevelFilter(LogLevel logLevel) const -> bool {
        return logLevel <= envConfig.displayedLogLevel;
    }



    /// Timestamp
    inline auto addTimestamp() -> LogStream & {
        const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        /// now as dd. MMM yyyy hh:mm:ss
        const time_t nowTime = std::chrono::system_clock::to_time_t(now);
        const auto totalDateFormat = envConfig.dateFormat + " | " + envConfig.timeFormat +  " | " ;

        stream << std::put_time(localtime(&nowTime), totalDateFormat.c_str());
        return *this;
    }

    /// Source location
    inline auto addSourcelocation(std::source_location const& location) -> LogStream & {
        const std::string filename = std::filesystem::path(location.file_name()).filename();
        stream << std::format( "  {}:{}:{}", filename, location.line(), location.column());
        return *this;
    }

    inline auto printEntryHeader(LogEntry const& logEntry) -> LogStream & {
        stream
//        << LogLevelHelper::BORDER
        << '|';
        addTimestamp();

        stream << logEntry.logLevel;

        if(logEntry.location.has_value()){
            addSourcelocation(logEntry.location.value());
        }

        stream << ' ' << '|';
//        LogLevelHelper::BORDER;
        return *this;
    }

    /// Colorized
    inline auto printColorizedEntryHeader(LogEntry const& logEntry) -> LogStream & {
        stream
        << LogLevelHelper::BOLD
        << LogLevelHelper::getColor(logEntry.logLevel);
//        << LogLevelHelper::BORDER

        addTimestamp();

        stream << logEntry.logLevel;

        if(logEntry.location.has_value()){
            addSourcelocation(logEntry.location.value());
        }

        stream
        << ' '
//        << LogLevelHelper::BORDER
        << LogLevelHelper::COLOR_RESET
        << LogLevelHelper::THIN
        << ' ';
        return *this;
    }


public:

    /// Singleton
    static auto create(EnvConfig const& envConfig) -> LogStream& {
        static LogStream logStream = LogStream(envConfig);
        return logStream;
    }

    static auto create(EnvConfig const& envConfig, std::ostream &ofstream) -> LogStream& {
        static LogStream logStream = LogStream(envConfig, ofstream);
        return logStream;
    }

    template<typename T>
    auto operator<<(T const &t) -> LogStream & {
        stream << t;
        return *this;
    }

     auto operator<<(std::ostream const&(*f)(std::ostream &)) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(std::ios const&(*f)(std::ios &)) -> LogStream & {
        stream << f;
        return *this;
    }

    auto operator<<(std::ios_base const&(*f)(std::ios_base &)) -> LogStream & {
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
            stream << logLevel;
        return *this;
    }

    auto operator << (LogEntry const& logEntry) -> LogStream & {
        bool entryFiltered = !logLevelFilter(logEntry.logLevel);

        if(entryFiltered) {
            return *this;
        }

        envConfig.colorize
            ? printColorizedEntryHeader(logEntry)
            : printEntryHeader(logEntry);
        stream << logEntry.message << std::endl;

        return *this;
    }

    auto is_open() -> bool {
        return stream.good();
    }

    auto operator << (std::filesystem::path const& path) -> LogStream & {
        stream << path;
//        std::ofstream ofs(path);
//        if(ofs.is_open()){
//            stream = ofs;
//        }
        return *this;
    }

};
