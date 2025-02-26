#pragma once

#include <token\Token.hpp>

#include <exception\ParserError.hpp>

namespace comet {

class UnexpectedTokenError : public ParserError {

public:

    UnexpectedTokenError(const TokenType &expected, const TokenType &actual);

};


}