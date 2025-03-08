#pragma once

#include <string>
#include <list>
#include <vector>

#include <filesystem>

namespace comet {
    
class Project;

namespace console {

    namespace fs = std::filesystem;

    void parseArguments(int argc, const char **args);

    void parseCommand();

    void readScript();

    /*============================Console commands============================*/

    void init(fs::path where);
    
    
    // Build command

    void build();

    /**
     * @brief This function prints inforamation of project 
     * 
     */
    void info();

    /**
     * This function returns vector of indexes on that places
     * flags (words that starts with '-')
     * 
     */
    std::vector<std::size_t> getFlags();


    std::string getStandartFlag(Project *target);


    // returns list of directories
    std::string getDirectory(std::string dir);

}


} // namespace comet
