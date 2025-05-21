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
    
    void parseCommand(std::string command);
    
    void parseCommand();

    void readScript();

    /*============================Console commands============================*/

    /**
     * @brief Creates ".xconfig" file in sepcified folder
     * 
     * @param where 
     */
    void init(fs::path where);
    
    
    /**
     * @brief Performs compilation and linking. If object path isn't specified
     * peroforms only linking from source files.
     */
    void build();

    /**
     * @brief This function prints inforamation of project 
     * 
     */
    void info();

    /**
     * @brief Activates terminal mode
     * 
     */
    void terminal();

    /**
     * @brief Links object or source files
     * 
     */
    void link();

    /**
     * This function returns vector of indexes on that places
     * flags (words that starts with '-')
     * 
     */
    std::vector<std::size_t> getFlags();


    std::string getStandartFlag(Project *target);


    // returns list of directories
    std::string getDirectory(std::string dir);

    const std::string &getCommand();

}


} // namespace comet
