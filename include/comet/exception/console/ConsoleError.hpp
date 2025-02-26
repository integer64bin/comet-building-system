#pragma once 

#include <stdexcept>
#include <string>

namespace comet {

/**
 * Describes class of error that occurs during command's
 * parsing, subprocess executions
 */

class ConsoleError : public std::runtime_error {
protected:

    int m_code = 0;

    std::string m_message;

public:

    ConsoleError();

    ConsoleError(const std::string &messgae, int code = 0);


    const char* what() const noexcept override;

};


}
