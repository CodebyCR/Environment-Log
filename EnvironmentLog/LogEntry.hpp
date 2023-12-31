//
// Created by Christoph Rohde on 19.12.23.
//

#pragma once

#include "LogLevel.hpp"

#include <iostream>
#include <string_view>

struct LogEntry{
public:
    LogLevel logLevel;
    std::string_view message;

};


