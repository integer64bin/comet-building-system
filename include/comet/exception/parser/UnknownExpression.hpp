#pragma once

#include <exception\ParserError.hpp>

namespace comet {

class UnknownExprssionError : public ParserError {
public:

    UnknownExprssionError(const std::string& error);

    // const char* what() const noexcept override;


};

}