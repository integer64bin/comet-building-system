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

    /*============================Console command============================*/

    void init(fs::path where);
    
    
    // Build command

    void build();


                      /*----------Support functions---------*/

    /**
     * @brief Compiles all files that project has, saves result to folder of
     * object files. After compilation performs linking of obj files.
     * If compilation errors occur doesn't perfrom linking
     */
    // void buildWithObjFiles();

    /**
     * @brief Compiles only specified files, saves result to folder of
     * object files. After compilation performs linking of obj files.
     * If compilation errors occur doesn't perfrom linking
     * 
     * If names empty compiles all source files
     * 
     * @param names list of names of source files
     */
    void buildWithObjFiles(std::list<std::string> names = {});
    
    // Compiles immediatly
    
    // 
    void initObjDirectories(std::string objDirectory);
    
    void buildFromSource();

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
