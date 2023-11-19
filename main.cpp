
#include "EnviormentLog.hpp"
#include "testHeader.hpp"


#include <iostream>
#include <string>


int main() {
    std::string logPath = std::filesystem::current_path() / "logs";
    std::cout << "Log to: " << logPath << std::endl;

    auto log = Log::EnviormentLog();
    log.print("Hello ${0} ${1}",
              {"World", "!"},
              std::source_location::current());

    log.print("test with one");

    log.print(__FILE_NAME__);

    log.error("test error");

    log.print("test print");

    test_space::TestClass testClass;




    return 0;
}


