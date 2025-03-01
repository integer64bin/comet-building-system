#include <iostream>
#include <typeinfo>

#include <Script.hpp>

#include <util.hpp>

#include <Lexer.hpp>
#include <Parser.hpp>

#include <exception\ParserError.hpp>

namespace comet {

Script::Script(const std::string &path) {
    m_data = readFile(path);
}

Script::~Script() {
    for(auto st : m_statements) {
        if(st == nullptr) {
            delete st;
        }
    }
}


void Script::perform() {
    
    Lexer lexer(m_data);

    Parser parser(lexer.tokenize(), *this);

    try {
        parser.parse();
    } catch(ParserError &e) {
        std::cerr << "An error occurred during execution" << std::endl;
        std::cerr << e.what() << std::endl;
        std::exit(1);
    }
}


void Script::execute() {
    for(auto st : m_statements) {
        if(st) {
            try{
                st->execute();
            } catch(...) { 
                throw; // All exceptions handles in console.cpp
            }
        }
    }
}



void Script::addStatement(Statement *st) {
    m_statements.push_back(st);
}


}