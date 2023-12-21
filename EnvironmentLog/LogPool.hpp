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
    std::filesystem::path logDirectory;

public:
    explicit LogPool(std::filesystem::path const &logDirectory) : logDirectory(logDirectory) {
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

        return {Log(logPath)};
    }

    /// Try to create a new log, if it does not exist.
    /// @return the created log or an empty optional.
    auto createLog(std::string_view logSubDirectory) -> std::optional<Log> {
        const auto logPath = logDirectory / logSubDirectory;
        if (!std::filesystem::exists(logPath)) {
            std::filesystem::create_directory(logPath);
        }
        this->insert(std::make_pair(logPath, Log(logPath)));
        return {this->at(logPath)};
    }
};

