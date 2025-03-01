#pragma once

#include <exception\execution\ExecutionError.hpp>

namespace comet {


    
class UnknownVariable : public ExecutionError {

public:

    UnknownVariable(const std::string &name);

};


}