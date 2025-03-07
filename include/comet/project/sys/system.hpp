#pragma once

#include <string>

#include <filesystem>
#include <chrono>

namespace comet {

namespace system {

    namespace fs = std::filesystem;

    const auto elapse = fs::file_time_type::clock::now().time_since_epoch()
                      - std::chrono::system_clock::now().time_since_epoch();

    bool createProcess(std::string name, std::string args);
 
    std::string identifyErrorCode(int code);

    void init();

    void finalize();

}

}