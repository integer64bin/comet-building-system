#pragma once

#include <string>

#include <stdexcept>

namespace comet {


/**
 * @brief Represents kind of errors that occurs during script execution
 * 
 */
class ExecutionError : public std::runtime_error {
protected:

    std::string m_message;

public:

    ExecutionError();

    ExecutionError(const std::string &message);

    const char *what() const noexcept override;

};


}