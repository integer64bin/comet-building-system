#pragma once

#include <exception\console\CommandError.hpp>

namespace comet {

class SubprocessError : public ConsoleError {
public:

    SubprocessError(const std::string &message, int errorCode);


private:

    std::string identifyErrorCode(int code);

};


}