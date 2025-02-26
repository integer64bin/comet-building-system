#pragma once

#include <exception\console\ConsoleError.hpp>

namespace comet {


class CommandError : public ConsoleError {

public:

    CommandError() = default;

    CommandError(const std::string &message);
    
};



class UnknownCommand : public CommandError {

};



class InvalidArgument : public CommandError {

};


}