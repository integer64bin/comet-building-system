#include <exception\console\SubprocessError.hpp>

#include <project\sys\system.hpp>

namespace comet {


SubprocessError::SubprocessError(const std::string &message, int errorCode)
                 : ConsoleError(message, errorCode) {
    if(m_code == 0) {
        m_message.append("No errors");
    } else
        m_message.append(identifyErrorCode(m_code));
}


std::string SubprocessError::identifyErrorCode(int code){
    return identifyErrorCode(code);
}

}