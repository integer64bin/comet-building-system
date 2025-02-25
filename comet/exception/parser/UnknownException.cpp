#include <exception\parser\UnknownExpression.hpp>

namespace comet {

UnknownExprssionException::UnknownExprssionException(
    const std::string &message
) : ParserException(message) { } 


}