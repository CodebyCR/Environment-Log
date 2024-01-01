

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
        .displayedLogLevel = LogLevel::INFO,
        .colorize = true,
        .stream = std::cout
    });



    log.print("Hello ${0} ${1}",
              {"World", "!"},
              std::source_location::current());

    log.print("test with one");

    log.print(__FILE_NAME__);

    log.error("test error");

    log.print("test print");

    test_space::TestClass testClass;


    // Colorized for individual log or MutltiStream

    log.print("-- Hello ${0} ${1} --","World", "!");
//    log.print("with source location", std::source_location::current());

    log.debug("Test ausgabe 1: Test debug");
    log.print("Test ausgabe 2: Test print");
    log.info("Test ausgabe 2: Test info");
    log.warning("Test ausgabe 3: Test warning");
    log.error("Test ausgabe 4: Test error");
    log.fatal("Test ausgabe 5: Test fatal");


    return 0;
}


