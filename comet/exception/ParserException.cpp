#include <exception\ParserException.hpp>

namespace comet {

ParserException::ParserException(const std::string& message) : m_message(message) { }

const char *ParserException::what() const {
    return m_message.c_str();
}

}