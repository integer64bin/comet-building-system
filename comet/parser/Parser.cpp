#include <Parser.hpp>

#include <iostream>
#include <cstdlib>

// Expressions
#include <ast\expression\NumberExpression.hpp>
#include <ast\expression\StringExpression.hpp>
#include <ast\expression\AccessExpression.hpp>

// Statements
#include <ast\statement\FunctionStatement.hpp>
#include <ast\statement\AssignmentStatement.hpp>

// Exceptions
#include <exception\parser\UnknownExpression.hpp>
#include <exception\parser\UnexpectedToken.hpp>

#include <util.hpp>

namespace comet {

const Token Parser::eof(TokenType::EOF_, "", 0);


Parser::Parser(std::vector<Token> tokens, Script &target) : 
    m_tokens(tokens), 
    script(target) {
    m_index = 0;
}


Script Parser::parse() {
    while(true) {
        if(look(TokenType::WORD)) {
            if(look(TokenType::LPAREN, 1)) {
                // function parsing
                functionStatement();
                continue;
            } else if(look(TokenType::EQ, 1)) {
                // assignment statement
                assignmentStatement();
                continue;
            }
        } //else if(look(TokenType::EOF_))
        break;
    }
    return script;
}

Token Parser::get(std::size_t relativePos) {
    if(m_index + relativePos >= m_tokens.size()) 
        return eof;
    return m_tokens[m_index + relativePos];
}

bool Parser::match(TokenType type, std::size_t relativePos) {
    if(get(relativePos).getType() == type)
        m_index++;
        return true;
    return false;
}

bool Parser::look(TokenType type, std::size_t relativePos) {
    if(get(relativePos).getType() == type)
        return true;
    return false;
}

/*
* Consumes token with TokenType type,
* if types don't match throws exception
*/
void Parser::consume(TokenType type) {
    if(match(type)) return;
    else {
        throw UnexpectedTokenError(type, get(0).getType());
    }
}

Token Parser::next() {
    Token t = get();
    m_index++;
    return t;
}


// Adds to script function 


void Parser::functionStatement() {
    std::string funcName = next().getText();
    std::vector<Expression*> arguments;

    // Skips '('
    consume(TokenType::LPAREN);
    while(!look(TokenType::RPAREN)) {
        // pushing all arguments to vector
        Expression *arg = expression();
        // Alocated memory will be free in 
        // FunctionStatement destructor
        arguments.push_back(arg);
        // skips ','
        if(match(TokenType::COMMA)) {
            continue;
        }
        break;
    }
    // Skips ')'
    consume(TokenType::RPAREN);
    script.addStatement(new FunctionStatement(funcName, arguments));
}


void Parser::assignmentStatement() {
    std::string varName = next().getText();
    consume(TokenType::EQ);
    Expression *value = expression();

    script.addStatement(new AssignmentStatement(varName, value));
}


Expression *Parser::expression() {
    return primary();
}

Expression *Parser::primary() {
    Expression *result = nullptr;
    if(look(TokenType::NUMBER)) {
        result = new NumberExpression( next().getText() );
    } else if(look(TokenType::TEXT)) {
        result = new StringExperssion( next().getText() );
    } else if(look(TokenType::WORD)) {
        result = new AccessExpression( next().getText() );
    } else {
        throw UnknownExprssionError(
            std::string("at line ").append(std::to_string(get(0).getLine()))
        );
    }
    return result;
}


}