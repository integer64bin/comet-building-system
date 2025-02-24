#pragma once

#include <string>
#include <list>
#include <set>

#include <filesystem>

namespace comet {
    
class Project;

namespace console {

    namespace fs = std::filesystem;
    
    void parseArguments(int argc, const char **args);

    void parseCommand(std::string command, std::string *args, int argc);

    void readScript();

    /*============================Console command============================*/

    void setup(fs::path where);
    
    void build(std::string name);

                      /*----------Support functions---------*/

    // Building support
    // Creates o-files
    void _buildWithObjFiles(Project *p);

    // Compiles immediatly
    void _buildFromSource(Project *p);

    // 
    void initObjDirectories(
        Project *t, 
        std::string objDirectory
    );

    // include supprot
    std::string getIncludeFlags(Project *target);

    // standart specifying support
    std::string getStandartFlag(Project *target);



    // returns list of directories
    std::set<std::string> getDirectories(std::list<std::string> files);

    std::string getDirectory(std::string dir);

}


} // namespace comet
