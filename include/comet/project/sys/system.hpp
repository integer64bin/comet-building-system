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

    namespace ui {

        enum color {
            black        = 0x0,
            dark_green   = 0x2,
            dark_cyan    = 0x3,
            dark_red     = 0x4,
            dark_magenta = 0x5,
            dark_yellow  = 0x6,
            dark_grey    = 0x7,
            grey         = 0x8,
            blue         = 0x9,
            green        = 0xA,
            cyan         = 0xB,
            red          = 0xC,
            magenta      = 0xD,
            yellow       = 0xE,
            white        = 0xF
        };

        void setFontColor(color foreground, color background = black);

    }

}

}