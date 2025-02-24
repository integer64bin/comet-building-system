#pragma once

#include <vector>

#include <token\Token.hpp>
#include <Script.hpp>

#include <ast\expression\Expression.hpp>

namespace comet {

class Parser {

    static const Token eof;

    std::vector<Token> m_tokens;

    // Current token
    std::size_t m_index;

    
    Script &script;


public:
    
    Parser(std::vector<Token> tokens, Script &target);

    /* ".xconfig" -- script, wicth contains only variables
     * and functions.
     * Now can use only system functions, all functions
     * decalred in Project.hpp
     */

    Script parse();


private:

    // Special parse performers


    // Statements
    void functionStatement();

    void assignmentStatement();

    // expression

    Expression *expression();

    Expression *primary();


    Token get(std::size_t relativePos = 0);

    bool match(TokenType type, std::size_t relativePos = 0);

    bool look(TokenType type, std::size_t relativePos = 0);


    /*
     * Consumes token with TokenType type,
     * if types don't match throws exception
     */
    void consume(TokenType type);

    Token next();

};



}