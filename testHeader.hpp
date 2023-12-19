//
// Created by Christoph Rohde on 16.10.23.
//

#pragma once

#include "EnviormentLog/EnviormentLog.hpp"
#include <iostream>

namespace test_space{
    class TestClass {
    public:
        TestClass() {
            std::cout << "TestClass created" << std::endl;

            auto log = EnviormentLog();
            log.print("Hello ${0} ${1}",{"World", "!"},std::source_location::current());
        }
    };
}

