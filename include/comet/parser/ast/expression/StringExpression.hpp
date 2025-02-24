#pragma once

#include <ast\expression\Expression.hpp>

namespace comet {


class StringExperssion : public Expression {

    StringValue *m_value;

public:

    StringExperssion(std::string_view text);
    
    ~StringExperssion();

    Value *eval() override;

};


}