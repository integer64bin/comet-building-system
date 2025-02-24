#pragma once

#include <ast\expression\Expression.hpp>
#include <ast\value\Value.hpp>

namespace comet {


class NumberExpression : public Expression {

    NumberValue *m_value;

public:

    NumberExpression(std::string_view text);

    ~NumberExpression();

    Value *eval() override;

};


}