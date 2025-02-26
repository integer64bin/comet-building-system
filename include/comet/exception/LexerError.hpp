#pragma once

#include <string>
#include <exception>

/**
 * Describes class of errors that occurs during
 * lexical analysis, such as unknown punctuation
 * signs, incorrect number format and other
 * 
 * @see UnknownPunct, IncorrectNumberFormat
 */

class LexerException : public std::exception {

    const char *m_message;

public:

    LexerException(const std::string& message);

    LexerException(const char *message);

    const char* what() const noexcept override;

};