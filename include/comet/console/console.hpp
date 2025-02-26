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

    void setup(fs::path where);
    
    
    // Build command

    void build(std::string name);

    /**
     * This function parses build flags. 
     * 
     * Searches strings which starts with '-', after sets value of required
     * flags
     * 
     * Flags:
     * -debug-info
     * -save-info
     * -f
     * -V
     * -r
     * -to
     */
    void parseBuildFlags();


                      /*----------Support functions---------*/

    // Building support
    // Creates o-files
    void buildWithObjFiles(Project *p);

    // Compiles immediatly
    
    // 
    void initObjDirectories(
        Project *t, 
        std::string objDirectory
    );
    
    void buildFromSource(Project *p);

    void buildOnly(std::list<std::string> files);

    /**
     * This function returns vector of indexes on that places
     * flags (words that starts with '-')
     * 
     */
    std::vector<int> getFlags();


    std::string getStandartFlag(Project *target);


    // returns list of directories
    std::string getDirectory(std::string dir);

}


} // namespace comet
