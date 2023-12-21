cmake_minimum_required(VERSION 3.20...3.24)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 8)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

project(EnvironmentLogBinary
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "A log tool for the whole environment."
        LANGUAGES CXX)

message(NOTICE "${PROJECT_NAME}: ${PROJECT_VERSION}")

SET(LOG_LIBRARY "EnvironmentLog")

add_subdirectory(${LOG_LIBRARY})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} INTERFACE
        "testHeader.hpp"
        ${LOG_LIBRARY})

