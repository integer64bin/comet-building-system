#include <ast\statement\AssignmentStatement.hpp>

#include <project\project.hpp>

#include <iostream>

namespace comet {

AssignmentStatement::AssignmentStatement(
    std::string_view varName, 
    Expression *value) : m_varName(varName.data()), m_value(value) { }


AssignmentStatement::~AssignmentStatement() {
    delete m_value;
}

void AssignmentStatement::execute() {
    try {
        setVariable(m_varName, m_value->eval());
    } catch(...) {
        throw;
    }
}

}