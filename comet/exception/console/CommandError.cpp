#include <exception\console\CommandError.hpp>


namespace comet {



CommandError::CommandError(const std::string &message)
              : ConsoleError(message, 1) { }

/**
 * UnknownCommand error
 */
UnknownCommand::UnknownCommand(const std::string &command) {
    m_message.append("Unknown command ")
             .append(command)
             .append(" use 'help' to view the list of commands");
    m_code = 1;
}

/**
 * UnknownProject error
 */
UnknownProject::UnknownProject(const std::string &name) {
    m_message = "Unknown project use 'projects list' to view list of projects";
}

/**
 * InvalidArgument error
 */
InvalidArgument::InvalidArgument(const std::string &name) 
                 : CommandError(name) {

}


}