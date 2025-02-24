#pragma once

#include <string>
#include <vector>

#include <ast\statement\Statement.hpp>
#include <ast\expression\Expression.hpp>

namespace comet {

class FunctionStatement : public Statement {
    
    std::string m_funcName;

    std::vector<Expression *> m_arguments;

public:

    FunctionStatement(
        std::string_view funcName,
        std::vector<Expression *> args
    );

    ~FunctionStatement();

    void execute() override final;

private:

    std::vector<Value*> evalArguments();

};

}