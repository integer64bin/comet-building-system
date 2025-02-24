#pragma once

#include <ast\value\Value.hpp>

namespace comet {

class Expression {
public:

    virtual ~Expression() = default;

    virtual Value *eval() = 0;

};



} // namespace comet
