#include <ast\expression\StringExpression.hpp>
#include <ast\expression\NumberExpression.hpp>
#include <ast\expression\AccessExpression.hpp>

#include <project\project.hpp>

#include <exception\execution\UnknownVariable.hpp>

namespace comet {
    
/*=============================String expression=============================*/

StringExperssion::StringExperssion(std::string_view value) {
    m_value = new StringValue( value.data() );
}


StringExperssion::~StringExperssion() {
    delete m_value;
}



Value *StringExperssion::eval() {
    return m_value;
}



/*=============================Number expression=============================*/

NumberExpression::NumberExpression(std::string_view text) {
    m_value = new NumberValue(text.data());
}


NumberExpression::~NumberExpression() {
    delete m_value;
}



Value *NumberExpression::eval() {
    return m_value;
}



AccessExpression::AccessExpression(std::string_view name) : m_name(name.data()) {}


Value *AccessExpression::eval() {
    if(Projects::target->contains(m_name.data()))
        return Projects::target->getVaribale(m_name);
    throw UnknownVariable(m_name);
}

} // namespace comet
