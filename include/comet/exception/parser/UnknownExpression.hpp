#pragma once

#include <exception\ParserException.hpp>

namespace comet {

class UnknownExprssionException : public ParserException {
public:

    UnknownExprssionException(const std::string& error);

    const char* what() const noexcept override;


};

}