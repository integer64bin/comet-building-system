#pragma once

#include <string>
#include <vector>

#include <ast\expression\Expression.hpp>
#include <ast\statement\Statement.hpp>

namespace comet {

class AssignmentStatement : public Statement {
    
    std::string m_varName;

    Expression *m_value;

public:

    AssignmentStatement(std::string_view funcName, Expression *value);

    ~AssignmentStatement();

    void execute() override final;

};

}