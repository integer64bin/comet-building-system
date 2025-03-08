#pragma once

#include <string>
#include <ostream>

namespace comet {


enum TokenType {

    // builtin types
    WORD, 
    NUMBER,
    TEXT,
    TRUE,
    FALSE,

    // keywords
    IF,
    ELSE,

    // Punct
    LPAREN = '(',
    RPAREN = ')',

    LBRACE = '{',
    RBRACE = '}',

    COMMA = ',',
    COLON = ':',

    DOLLAR = '$',
    QM = '?',

    EQ = '=',

    EOF_ = -1,

};

class Token {
    // main info
    const TokenType m_type;
    const std::string m_text;

    // debug info

    const size_t m_line;

public:

    Token(TokenType type, std::string text, std::size_t line);

    TokenType getType() const;

    std::string getText() const;

    std::size_t getLine() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &t);

};

std::string_view asString(comet::TokenType type);


}