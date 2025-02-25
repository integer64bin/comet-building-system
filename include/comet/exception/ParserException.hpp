#pragma once

#include <string>
#include <exception>

namespace comet {

class ParserException : public std::exception {
protected:

    std::string m_message;

public:

    ParserException() = default;

    ParserException(const std::string& message);

    const char* what() const noexcept override;

};

}