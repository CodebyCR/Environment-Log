//
// Created by Christoph Rohde on 14.10.23.
//

#pragma once

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

namespace LogColor{ // Test
    constexpr std::string_view Red = "\033[0;31m";


    struct ColorToggle{
    private:
        std::string_view color;

    public:
        explicit ColorToggle(std::string_view color) : color(color) {}

        auto operator()(const bool colorized) -> std::string_view {
            return colorized ? color : "";
        }
    };

    ColorToggle redToggle(Red);
    auto result = redToggle(true);
}

namespace Log {
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

        struct EnvConfig{
        public:
            std::filesystem::path logDirectory;
            std::string dateFormat;
            std::string timeFormat;
            LogLevel logLevel;
            bool colorize;
        };

        class Log {
        private:
            std::filesystem::path logPath;

        public:

            Log(std::filesystem::path const& logPath) : logPath(logPath) {}

            /// create dirfrent kinds of log entries here...

        };



        class EnviormentLog {
        private:
            EnvConfig envConfig;

            /// Note: maybe use impl. pattern
            class LogPool : std::map<std::filesystem::path, Log> {
            private:
                std::filesystem::path logDirectory;

            public:
                LogPool(std::filesystem::path const& logDirectory) : logDirectory(logDirectory) {
                    if (!std::filesystem::exists(logDirectory)) {
                        std::filesystem::create_directory(logDirectory);
                    }
                }

                /// Gives you a log if it exists.
                /// @return the existing log or an empty optional.
                auto getLog(std::string_view logSubDirectory) -> std::optional<Log> {
                    const auto logPath = logDirectory / logSubDirectory;
                    if (!std::filesystem::exists(logPath)) {
                        return std::nullopt;
                    }

                    return std::make_optional<Log>(Log(logPath));
                }

                /// Try to create a new log, if it does not exist.
                /// @return the created log or an empty optional.
                auto createLog(std::string_view logSubDirectory) -> std::optional<Log> {
                    const auto logPath = logDirectory / logSubDirectory;
                    if (!std::filesystem::exists(logPath)) {
                        std::filesystem::create_directory(logPath);
                    }
                    this->insert(std::make_pair(logPath, Log(logPath)));
                    return std::optional<Log>(this->at(logPath));
                }
            };
            LogPool logPool;

        public:
            EnviormentLog(EnvConfig const& envConfig = {
                    .logDirectory = std::filesystem::current_path() / "logs",
                    .dateFormat = "%d. %b %Y",
                    .timeFormat = "%T",
                    .logLevel = LogLevel::INFO,
                    .colorize = true
            }) : envConfig(envConfig), logPool(envConfig.logDirectory) {
                std::cout << "test print" << std::endl;
            }

            auto getLog(std::string_view logSubDirectory) -> std::optional<Log> {
                return logPool.getLog(logSubDirectory);
            }

            auto createLog(std::string_view logDirectory) -> std::optional<Log> {
                return logPool.createLog(logDirectory);
            }

            auto interpolateArgs(std::string_view logInfo,
                                 const std::vector<std::string_view> &arguments) -> std::string {
                std::string info = logInfo.data();

                for(int8_t index = 0; index < arguments.size(); index++) {
                    const std::regex pattern ("\\$\\{" + std::to_string(index) + "\\}");
                    const std::string replacement(arguments[index]);
                    info = std::regex_replace(info, pattern , replacement);
                }
                return info;
            }

//            auto currentSource(std::stringstream& stream,
//                               std::optional<std::source_location> const& caller) -> std::string {
//
//
//                return stream.str();
//            }

//            inline auto getTimestamp(std::stringstream& stream,) -> std::stringstream  {
//
//
//                return stream;
//            }




            auto error(std::string_view logInfo,
                       std::vector<std::string_view> const& arguments = {},
                       std::optional<std::source_location> caller = std::nullopt) -> void {
                const std::string info = interpolateArgs(logInfo, arguments);
                constexpr std::string_view Error = "ERROR";
                constexpr std::string_view Red = "\033[0;31m";
                constexpr std::string_view Reset = "\033[0m";

                auto stream = std::stringstream();
                stream << "[ " << Red << Error  << ' ';
//                stream = getTimestamp(stream);

                const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                /// now as dd. MMM yyyy hh:mm:ss
                const time_t nowTime = std::chrono::system_clock::to_time_t(now);

                const auto totalDateFormat = "| " + envConfig.timeFormat + " | " + envConfig.dateFormat;
                stream << std::put_time(localtime(&nowTime), totalDateFormat.c_str());

                if (caller.has_value()) {
                    const auto filename = std::filesystem::path(caller->file_name()).filename().c_str();
                    stream << " | " << filename << ':' << caller->line()
                           << " (" << caller->line() << ':' << caller->column() << ")";
                }

                stream << Reset << " ] -> " << info << std::endl;

                std::cout << stream.str();
            }


            template<typename ...Args>
            auto print(std::string_view logInfo,
                       std::vector<std::string_view> const& arguments = {},
                       std::optional<std::source_location> caller = std::nullopt) -> void {

                const std::string info = interpolateArgs(logInfo, arguments);
                constexpr std::string_view Info = "INFO";

                auto stream = std::stringstream();
                stream << "[ " << Info << ' ';
//                stream = getTimestamp(stream);

                const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                /// now as dd. MMM yyyy hh:mm:ss
                const time_t nowTime = std::chrono::system_clock::to_time_t(now);

                const auto totalDateFormat = "| " + envConfig.timeFormat +  " | " + envConfig.dateFormat;
                stream << std::put_time(localtime(&nowTime), totalDateFormat.c_str());

                if(caller.has_value()){
                    const auto filename = std::filesystem::path(caller->file_name()).filename().c_str();
                    stream <<  " | " << filename <<  ':' << caller->line()
                            << " (" << caller->line() << ':' << caller->column() << ")";
                }

                stream  << " ] -> " << info << std::endl;


                std::cout << stream.str();
            }




    };


        // get EnviormentLog as Sigelton unique ptr

};


