#pragma once 

#include <exception>
#include <string>

namespace comet {


class ConsoleError : public std::exception {
protected:

    int m_code = 1;

    std::string m_message;

public:

    ConsoleError() = default;

    ConsoleError(const std::string &messgae);


    const char* what() const noexcept override;

};


}
