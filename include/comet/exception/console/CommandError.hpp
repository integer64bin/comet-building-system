#pragma once

#include <exception\console\ConsoleError.hpp>

namespace comet {

/**
 * @brief Common class for occurring during command's parsing
 * errors
 */
class CommandError : public ConsoleError {

public:

    CommandError() = default;

    CommandError(const std::string &message);
    
};


/**
 * @brief This error occurs when passed unknown command
 * to comet
 */
class UnknownCommand : public CommandError {

    

public:

    UnknownCommand() = default;

    UnknownCommand(const std::string &command);

    /**
     * @brief Perform search in list of command and return the most similar
     * command
     * @param command command that need to find 
     * @return std::string 
     */
    std::string findSimilar(std::string_view command);

};

/**
 * @brief This error occurs when user access to non-existent
 * project
 * 
 * 
 */
class UnknownProject : public CommandError {
public:

    UnknownProject() = default;

    UnknownProject(const std::string &name);

};


/**
 * @brief 
 * 
 */
class InvalidArgument : public CommandError {
public:

    InvalidArgument() = default;

    InvalidArgument(const std::string &name);

};


}