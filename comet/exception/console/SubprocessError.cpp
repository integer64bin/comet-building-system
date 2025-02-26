#include <exception\console\SubprocessError.hpp>

#include <project\sys\system.hpp>

namespace comet {

SubprocessError::SubprocessError(int code) : SubprocessError("", code) { }

SubprocessError::SubprocessError(const std::string &message, int errorCode)
                 : ConsoleError(message, errorCode) {
    if(m_code == 0) {
        m_message.append("No errors");
    } else
        m_message.append(identifyErrorCode());
}


std::string SubprocessError::identifyErrorCode() {
    return system::identifyErrorCode(m_code);
}

}