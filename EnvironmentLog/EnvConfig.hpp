//
// Created by Christoph Rohde on 17.12.23.
//

#pragma once

#include "LogLevel.hpp"

#include <iostream>
#include <filesystem>

struct EnvConfig{
public:
    std::filesystem::path logDirectory;
    std::string dateFormat;
    std::string timeFormat;
    LogLevel logLevel;
    bool colorize;
};
