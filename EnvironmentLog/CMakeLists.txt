
# Log subdirectory
set(LOG_SOURCES
        "EnvConfig.hpp"
        "LogLevel.hpp"
        "LogStream.hpp"
        "LogPool.hpp"
        "Log.hpp"
        "EnvironmentLog.hpp")

add_library(${LOG_LIBRARY} INTERFACE ${LOG_SOURCES} )


target_include_directories( ${LOG_LIBRARY}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR} )