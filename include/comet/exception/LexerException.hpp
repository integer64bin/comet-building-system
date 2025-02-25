#pragma once

#include <string>
#include <exception>

class LexerException : public std::exception {

    const char *m_message;

public:

    LexerException(const std::string& message);

    LexerException(const char *message);

    const char* what() const noexcept override;

};