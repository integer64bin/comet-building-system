#include <exception\execution\UnknownVariable.hpp>
#include <exception\execution\UnknownFunction.hpp>

namespace comet {

ExecutionError::ExecutionError() : runtime_error("") { }

ExecutionError::ExecutionError(const std::string &message) 
                : m_message(message), runtime_error(message.c_str()) {

}

const char *ExecutionError::what() const noexcept {
    return m_message.c_str();
}


UnknownVariable::UnknownVariable(const std::string &name) {
    m_message.append("Unknown variable \"").append(name).push_back('"');
}


UnknownFunction::UnknownFunction(const std::string &name) {
    m_message.append("Unknown function \"").append(name).push_back('"');
}


}
