#pragma once

#include <token\Token.hpp>

#include <exception\ParserException.hpp>

namespace comet {

class UnexpectedTokenException : public ParserException {

public:

    UnexpectedTokenException(const TokenType &expected, const TokenType &actual);

};


}