#include <exception\console\CommandError.hpp>


namespace comet {


CommandError::CommandError() {
    
}

CommandError::CommandError(const std::string &message)
              : ConsoleError(message, 1) { }


}