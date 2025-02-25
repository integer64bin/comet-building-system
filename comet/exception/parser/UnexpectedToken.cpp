#include <exception\parser\UnexpectedToken.hpp>

namespace comet {

UnexpectedTokenException::UnexpectedTokenException(
    const TokenType &expected, 
    const TokenType &actual
) {
    m_message.append("Expected type ").append(asString(expected))
             .append(" provided type").append(asString(actual));
}


}