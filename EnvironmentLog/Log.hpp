    //
    // Created by Christoph Rohde on 17.12.23.
    //

    #pragma once

    #include "LogStream.hpp"

    #include <iostream>
    #include <filesystem>
    #include <utility>
    #include <optional>
    #include <vector>
    #include <string_view>
    #include <cstdarg>
    #include <regex>



    class Log {
    private:
        EnvConfig envConfig;
        LogStream logStream;

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
        explicit Log(EnvConfig const& envConfig, LogStream& outputStream) :
        envConfig(envConfig),
        logStream(outputStream) {}

        auto print(std::string_view logInfo,
                   std::vector<std::string_view> const &arguments = {},
                   std::optional<std::source_location> caller = std::nullopt) -> void {

            const std::string info = interpolateArgs(logInfo, arguments);

            const LogEntry logEntry = {
                    .logLevel = LogLevel::INFO,
                    .message =  info,
                    .location = caller
            };
            if (logStream.is_open()){
                logStream << logEntry;
            }
            else{
                std::cout << "LogStream is not open" << std::endl;
            }

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

        auto success(std::string_view message,
                     std::vector<std::string_view> const &arguments = {},
                     std::optional<std::source_location> caller = std::nullopt) -> void {

            const std::string info = interpolateArgs(message, arguments);

            const LogEntry logEntry = {
                    .logLevel = LogLevel::SUCCESS,
                    .message =  info,
                    .location = caller
            };

            logStream << logEntry;
        }
    };
