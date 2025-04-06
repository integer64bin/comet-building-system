#include <ast\statement\FunctionStatement.hpp>

#include <iostream>

#include <project\project.hpp>
#include <project\managament.hpp>

namespace comet {

FunctionStatement::FunctionStatement(
    std::string_view funcName,
    std::vector<Expression *> args
) : m_funcName(funcName.data()), m_arguments(args) {
    //std::cout << funcName << std::endl;
}


FunctionStatement::~FunctionStatement() {
    for(auto e : m_arguments) {
        delete e;
    }
}



void FunctionStatement::execute() {
    std::vector<Value*> args = evalArguments();
    Projects::call(m_funcName, args);
}



std::vector<Value*> FunctionStatement::evalArguments() {
    std::vector<Value*> result;
    for(auto e : m_arguments) {
        try {
            result.push_back(e->eval());
        } catch(...) {
            throw;
        }
    }
    return result;
}


}