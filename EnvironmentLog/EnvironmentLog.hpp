//
// Created by Christoph Rohde on 14.10.23.
//

#pragma once

#include "LogPool.hpp"
#include "LogLevel.hpp"
#include "EnvConfig.hpp"
#include "LogStream.hpp"

#include <iostream>
#include <filesystem>
#include <map>
#include <optional>
#include <string_view>
#include <string>
#include <regex>
#include <source_location>
#include <sstream>
#include <optional>
#include <memory>
#include <cstdarg>

class EnvironmentLog {
private:
    EnvConfig envConfig;
    LogPool logPool;
    LogStream logStream = LogStream::create(envConfig);

    static auto interpolateArgs(std::string_view logInfo,
                                std::vector<std::string_view> const &arguments) -> std::string {
        std::string info = logInfo.data();

        for (std::uint32_t index = 0; index < arguments.size(); index++) {
            const std::regex pattern("\\$\\{" + std::to_string(index) + "\\}");
            const std::string replacement(arguments[index]);
            info = std::regex_replace(info, pattern, replacement);
        }
        return info;
    }

public:

    explicit EnvironmentLog(EnvConfig const &envConfig = {
            .logDirectory = std::filesystem::current_path() / "logs",
            .dateFormat = "%d. %b %Y",
            .timeFormat = "%T",
            .displayedLogLevel = LogLevel::INFO,
            .colorize = true,
            .stream = std::cout
    }) : envConfig(envConfig), logPool(envConfig.logDirectory) {}

    auto getLog(std::string_view logSubDirectory) -> std::optional<Log> {
        return logPool.getLog(logSubDirectory);
    }

    auto createLog(std::string_view logDirectory) -> std::optional<Log> {
        return logPool.createLog(logDirectory);
    }

    auto print(std::string_view logInfo,
               std::vector<std::string_view> const &arguments = {},
               std::optional<std::source_location> caller = std::nullopt) -> void {

        const std::string info = interpolateArgs(logInfo, arguments);

        const LogEntry logEntry = {
                .logLevel = LogLevel::INFO,
                .message =  info,
                .location = caller
        };

        logStream << logEntry;
    }


    template<typename... Args>
    auto print(std::string_view logInfo, Args... args) -> void {
        std::vector<std::string_view> arguments{args...};
        print(logInfo, arguments);
    }

    auto info(std::string_view logInfo,
              std::vector<std::string_view> const &arguments = {},
              std::optional<std::source_location> caller = std::nullopt) -> void {

        print(logInfo, arguments, caller);
    }

    auto debug(std::string_view logInfo,
               std::vector<std::string_view> const &arguments = {},
               std::optional<std::source_location> caller = std::nullopt) -> void {

        const std::string info = interpolateArgs(logInfo, arguments);

        const LogEntry logEntry = {
                .logLevel = LogLevel::DEBUG,
                .message =  info,
                .location = caller
        };

        logStream << logEntry;
    }

    auto warning(std::string_view message,
                 std::vector<std::string_view> const &arguments = {},
                 std::optional<std::source_location> caller = std::nullopt) -> void {

        const std::string info = interpolateArgs(message, arguments);

        const LogEntry logEntry = {
                .logLevel = LogLevel::WARNING,
                .message =  info,
                .location = caller
        };

        logStream << logEntry;
    }

    auto error(std::string_view message,
               std::vector<std::string_view> const &arguments = {},
               std::optional<std::source_location> caller = std::nullopt) -> void {

        const std::string info = interpolateArgs(message, arguments);

        const LogEntry logEntry = {
                .logLevel = LogLevel::ERROR,
                .message =  info,
                .location = caller
        };

        logStream << logEntry;
    }

    auto fatal(std::string_view message,
               std::vector<std::string_view> const &arguments = {},
               std::optional<std::source_location> caller = std::nullopt) -> void {

        const std::string info = interpolateArgs(message, arguments);

        const LogEntry logEntry = {
                .logLevel = LogLevel::FATAL,
                .message =  info,
                .location = caller
        };

        logStream << logEntry;
    }


// TODO:
//  ~~skip logentry if loglevel is lower than loglevel of the log~~
//  ~~add one private methode for logentry~~
//  ~~logentry to logstream overload~~
//  ~~add togglebar color~~
//  ~~add togglebar loglevel~~
// add missing loglevels
// add & get sub logs


};