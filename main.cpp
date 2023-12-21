

#include "testHeader.hpp"



#include "EnvironmentLog/LogStream.hpp"
#include "EnvironmentLog/EnvironmentLog.hpp"


#include <iostream>
#include <filesystem>


int main() {
    std::filesystem::path logPath = std::filesystem::current_path() / "logs";
    std::cout << "Log to: " << logPath << std::endl;

    auto log = EnvironmentLog();
    log.print("Hello ${0} ${1}",
              {"World", "!"},
              std::source_location::current());

    log.print("test with one");

    log.print(__FILE_NAME__);

    log.error("test error");

    log.print("test print");

    test_space::TestClass testClass;



    LogStream logStream2 = LogStream::create(true, LogLevel::INFO);
    logStream2 << LogLevel::ERROR << " test error" << std::endl;
    logStream2 << LogLevel::INFO << " test info" << std::endl;

    LogStream logStream3 = LogStream::create(true, LogLevel::ERROR);
    logStream3 << LogLevel::ERROR << " test error" << std::endl;
    logStream3 << LogLevel::INFO << " test info" << std::endl;



    return 0;
}


