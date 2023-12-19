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

namespace LogColor { // Test
    constexpr std::string_view Red = "\033[0;31m";
}

//struct ColorToggle{
//private:
//std::string_view color;
//
//public:
//explicit ColorToggle(std::string_view color) : color(color) {}
//
//auto operator()(const bool colorized) -> std::string_view {
//    return colorized ? color : "";
//}
//};
//
//ColorToggle redToggle(Red);
//auto result = redToggle(true);
//}



class EnvironmentLog {
private:
    EnvConfig envConfig;
    LogPool logPool;
    LogStream logStream = LogStream::create(envConfig.colorize, envConfig.logLevel);


public:

    EnvironmentLog(EnvConfig const& envConfig = {
            .logDirectory = std::filesystem::current_path() / "logs",
            .dateFormat = "%d. %b %Y",
            .timeFormat = "%T",
            .logLevel = LogLevel::INFO,
            .colorize = true
    }) : envConfig(envConfig), logPool(envConfig.logDirectory) {
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




auto error( std::string_view logInfo,
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
auto print( std::string_view logInfo,
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

// TODO: skip logentry if loglevel is lower than loglevel of the log
// add one private methode for logentry to logstream
// add togglebar color
// add togglebar loglevel
// add missing loglevels
// add & get sub logs


};