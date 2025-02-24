#pragma once

#include <string>
#include <ostream>

namespace comet {


enum TokenType {

    WORD, 
    NUMBER,
    TEXT,

    // Punct
    LPAREN = '(',
    RPAREN = ')',

    COMMA = ',',
    COLON = ':',

    DOLLAR = '$',

    EQ = '=',

    EOF_ = -1,

};

class Token {
    const TokenType m_type;
    const std::string m_text;
public:

    Token(TokenType type, std::string text);

    TokenType getType() const;

    std::string getText() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &t);

};


}