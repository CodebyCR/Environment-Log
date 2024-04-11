//
// Created by Christoph Rohde on 17.12.23.
//

#pragma once

#include "Log.hpp"

#include <iostream>
#include <filesystem>
#include <map>
#include <optional>



/// Note: maybe use impl. pattern
class LogPool : std::map<std::filesystem::path, Log> {
private:
    EnvConfig envConfig;


    /// get file output stream from filepath
    /// @param logSubDirectory
    [[nodiscard]] auto getLogStream(std::string_view logSubDirectory) const -> std::optional<std::ofstream> {
        const auto logPath = envConfig.logDirectory / logSubDirectory;
        if (!std::filesystem::exists(logPath)) {
            return std::nullopt;
        }

        return {std::ofstream(logPath)};
    }

public:
    explicit LogPool(EnvConfig const& envConfig) : envConfig(envConfig) {
        if (!std::filesystem::exists(envConfig.logDirectory)) {
            std::filesystem::create_directory(envConfig.logDirectory);
        }
    }


    /// Gives you a log if it exists.
    /// @return the existing log or an empty optional.
    auto getLog(std::string_view logSubDirectory) -> std::optional<Log> {
        const auto logPath = envConfig.logDirectory / logSubDirectory / "logfile.log" ;
//        logPath += ".log";
        if (!std::filesystem::exists(logPath)) {
            return std::nullopt;
        }

//        auto fileOutStream = std::ofstream(logPath);
//        auto logstream = LogStream::create(envConfig, fileOutStream);
//        auto log = Log(envConfig, logstream);
//
//        std::cout << "Log file--: " << logPath << std::endl;
//
//
//        this->insert(std::make_pair(logSubDirectory, log));
        return {this->at(logSubDirectory)};
    }

    /// Try to create a new log, if it does not exist.
    /// @return the created log or an empty optional.
    auto createLog(std::string_view logSubDirectory) -> std::optional<Log> {
        const auto logPath = envConfig.logDirectory / logSubDirectory / "logfile.log";
        if (!std::filesystem::exists(logPath)) {
            std::filesystem::create_directory(logPath);
        }

        std::cout << "Log file: " << logPath << std::endl;
        auto fileOutStream = std::ofstream(logPath );
        fileOutStream << "test"; //Todo: works here? stream closed?

        auto logstream = LogStream::create(envConfig, fileOutStream);
        Log createdLogFile(envConfig, logstream);

        this->insert(std::make_pair(logSubDirectory, createdLogFile));

        std::cout << "Log file: " << logPath << std::endl;
        return {this->at(logSubDirectory)};
    }

};

