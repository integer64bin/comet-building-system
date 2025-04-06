#include <exception\console\ConsoleError.hpp>

namespace comet {

ConsoleError::ConsoleError() : runtime_error("") { }


ConsoleError::ConsoleError(const std::string &messgae, int code)
              : m_message(messgae), runtime_error(messgae.c_str()), m_code(code) { }


const char* ConsoleError::what() const noexcept {
    return m_message.c_str();
}


}