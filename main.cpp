

#include "testHeader.hpp"



#include "EnvironmentLog/LogStream.hpp"
#include "EnvironmentLog/EnvironmentLog.hpp"


#include <iostream>
#include <filesystem>


int main() {
    std::filesystem::path logPath = std::filesystem::current_path() / "logs";
    std::cout << "Log to: " << logPath << std::endl;

    // test log file
    std::filesystem::path logFilePath = logPath / "test.log";
    std::cout << "Log file: " << logFilePath << std::endl;

    // create log file
//    std::ofstream logFile(logFilePath);

    // TODO: create log file


    auto log = EnvironmentLog({
        .logDirectory = logPath,
        .dateFormat = "%d. %b %Y",
        .timeFormat = "%T",
        .displayedLogLevel = LogLevel::DEBUG,
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

    log.print("-- Hello ${0} ${1} --", "World", "!");
//    log.print("with source location", std::source_location::current());

    log.debug("Test debug");
    log.print("Test print");
    log.info("Test info");
    log.warning("Test warning");
    log.error("Test error");
    log.fatal("Test fatal with source location", {}, std::source_location::current());
    log.success("Test success");

    log.print("${0}Test bold print${1}", LogLevelHelper::BOLD, LogLevelHelper::THIN);


    log.createLog("optionalFileTest");
    auto optionalFileTest = log.getLog("optionalFileTest");
    if(optionalFileTest.has_value()){
        log.print("optionalFileTest created");
        optionalFileTest.value().print("optionalFileTest - are this in the log file?");
    } else {
        log.print("optionalFileTest not created");
    }

    log.print("optionalFileTest closed");

//    auto* log = new Log("testLog");


    return 0;
}


