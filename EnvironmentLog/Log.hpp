    //
    // Created by Christoph Rohde on 17.12.23.
    //

    #pragma once


    #include <filesystem>
    #include <utility>


    class Log {
    private:
        std::filesystem::path logPath;

    public:
        explicit Log(std::filesystem::path logPath) : logPath(std::move(logPath)) {}

        /// create dirfrent kinds of log entries here...
    };
