    //
    // Created by Christoph Rohde on 17.12.23.
    //

    #pragma once


    #include <filesystem>


    class Log {
    private:
        std::filesystem::path logPath;

    public:
        Log(std::filesystem::path const &logPath) : logPath(logPath) {}

        /// create dirfrent kinds of log entries here...
    };
