#pragma once

#include <vector>

#include <token\Token.hpp>

namespace comet {


class Lexer {
    // The source code
    std::string m_src;
    std::size_t m_length;

    // Index of current symbol
    std::size_t m_index;

    // Resulting list of tokens
    std::vector<Token> m_tokens;

    // debug info
    std::size_t m_line = 0;
    
    const static char eof;

public:

    Lexer(std::string &src);

    std::vector<Token> &tokenize();

private:
    // Special tokenizing operators

    void tokenizeNumber();

    void tokenizeOperator();

    void tokenizeWord();

    void tokenizeText();

    void tokenizeComments();

    // Supporting methods
    char get(size_t relativePos = 0);

    inline char peek();

    inline char next();


    inline bool isOperator();


    // List-util methods

    inline void add(
        TokenType type, 
        std::string text = "", 
        std::size_t line = 0
    );

};


}