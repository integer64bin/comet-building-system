#pragma once

#include <exception\execution\ExecutionError.hpp>

namespace comet {


class UnknownFunction : public ExecutionError {

    std::string m_name;

public:

    UnknownFunction(const std::string &name);

};

    
}