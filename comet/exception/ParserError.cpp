#include <exception\ParserError.hpp>

namespace comet {

ParserError::ParserError() : runtime_error("") { }


ParserError::ParserError(const std::string& message) 
             : m_message(message), runtime_error(message.c_str()) { }

             
const char *ParserError::what() const noexcept {
    return m_message.c_str();
}

}