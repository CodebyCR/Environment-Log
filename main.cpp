

#include "testHeader.hpp"



#include "EnvironmentLog/LogStream.hpp"
#include "EnvironmentLog/EnvironmentLog.hpp"


#include <iostream>
#include <filesystem>


int main() {
    std::filesystem::path logPath = std::filesystem::current_path() / "logs";
    std::cout << "Log to: " << logPath << std::endl;

    auto log = EnvironmentLog({
        .logDirectory = logPath,
        .dateFormat = "%d. %b %Y",
        .timeFormat = "%T",
        .logLevel = LogLevel::ERROR,
        .colorize = true
    });



    log.print("Hello ${0} ${1}",
              {"World", "!"},
              std::source_location::current());

    log.print("test with one");

    log.print(__FILE_NAME__);

    log.error("test error");

    log.print("test print");

    test_space::TestClass testClass;



    LogStream logStream2 = LogStream::create();
    logStream2 << std::endl;
    logStream2 << std::endl;



    LogEntry testEntry = {
            .logLevel = LogLevel::ERROR,
            .message = "test error message"
    };

    LogEntry testEntry2 = {
            .logLevel = LogLevel::INFO,
            .message = "test info message"
    };
//            .sourceLocation = std::source_location::current()
//    };

    logStream2 << "Test ausgabe 1: " << testEntry << std::endl;
    logStream2 << "Test ausgabe 2: " << testEntry2 << std::endl;


    LogStream logStream3 = LogStream::create();
    logStream3 << "Test ausgabe 3: " << testEntry << std::endl;
    logStream3 << "Test ausgabe 4: " << testEntry2 << std::endl;

    // Colorized for individual log or MutltiStream


    return 0;
}


