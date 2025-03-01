#pragma once

#include <string>

#include <ast\expression\Expression.hpp>

#include <exception\execution\UnknownVariable.hpp>

namespace comet {


class AccessExpression : public Expression {

    std::string m_name;

public:

    AccessExpression(std::string_view name);

    Value *eval() override;

};


}