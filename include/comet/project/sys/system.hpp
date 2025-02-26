#pragma once

#include <string>

namespace comet {

namespace system {

    bool createProcess(std::string name, std::string args);
 
    std::string identifyErrorCode(int code);

    void init();

    void finalize();

}

}