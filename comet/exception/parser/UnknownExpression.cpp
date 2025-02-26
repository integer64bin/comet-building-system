#include <exception\parser\UnknownExpression.hpp>

namespace comet {

UnknownExprssionError::UnknownExprssionError(
    const std::string &message
) : ParserError(message) {
    m_message.insert(0, "Unknown expression ");
} 


}