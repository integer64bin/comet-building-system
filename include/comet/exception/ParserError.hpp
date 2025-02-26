#pragma once

#include <string>
#include <stdexcept>


namespace comet {

/**
 * This class describes Parser unsolvable situation
 * if Parser throws this error, it means, that 
 * program cannot continue execution
 * 
 * Examples: UnexpectedToken, UnknonwExpression
 * */
class ParserError : public std::runtime_error {
protected:

    std::string m_message;

public:

    ParserError();

    ParserError(const std::string& message);

    const char* what() const noexcept override;

};

}