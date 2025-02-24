#include <iostream>
#include <typeinfo>

#include <Script.hpp>

#include <util.hpp>

#include <Lexer.hpp>
#include <Parser.hpp>

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

    parser.parse();

}


void Script::execute() {
    for(auto st : m_statements) {
        if(st) {
            st->execute();
        }
    }
}



void Script::addStatement(Statement *st) {
    m_statements.push_back(st);
}


}