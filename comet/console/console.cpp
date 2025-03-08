#include <console\console.hpp>

#include <iostream> // condole output
#include <fstream>  // file reading/writing
#include <chrono>

#include <format>
#include <locale>

#include <util.hpp>
#include <project\project.hpp>

#include <Script.hpp>

#include <exception\console\CommandError.hpp>
#include <exception\execution\ExecutionError.hpp>
#include <exception\execution\UnknownVariable.hpp>

namespace comet {

namespace console {

    namespace fs = std::filesystem;

    namespace chrono = std::chrono;

    using namespace std::chrono_literals;

    // Place from which called comet.exe
    //
    std::string workspace;

    //  
    std::string root = ".";

    // List of arguments
    std::vector<std::string> arguments;

    // Current project
    Project *current;


    /**
     * @brief Get the Working Directory object
     * 
     * @param line 
     * @return std::string 
     */

    std::string getWorkingDirectory(std::string &line) {
        auto i = line.size() - 1;
        for(; i >= 0; i--) {
            if(line[i] == '\\')
                break;
        }
        return line.substr(0, i);
    }
    
    void parseArguments(int argc, const char **argv) {

        if(argc == 1) {
            return;
        }

        arguments = makeStringVector(argc, argv);

        // after last '\' comes exe-file name
        // befor last '\' comes working directory
        workspace = getWorkingDirectory(arguments[0]);

        try { 
            parseCommand();
        } catch(ConsoleError &e) {
            std::cerr << "An error occured during command execution..." << std::endl;
            std::cerr << e.what() << std::endl;
            std::exit(1); 
        }
    }

    void parseCommand() {
        // Count of arguments without command and work directory
        int argc = arguments.size() - 2;

        std::string command = arguments[1];

        if(command.compare("init") == 0) {
            fs::path dir;
            if(argc == 0 || (argc == 1 && arguments[2].compare("."))) {
                dir = fs::path(workspace);
            } else {
                dir = fs::path(workspace + "\\" + arguments[2]);
            }

            init(dir);

         
        } else if(command.compare("help") == 0) {
            
        } else { // commands that require script
            readScript();
            if(command.compare("build") == 0) {
                build();
            } else if(command.compare("link") == 0) {

            } else if(command.compare("info") == 0) {
                info();
            }
        }
    }



    void readScript() {
        Script script(workspace + "\\.xconfig");

        script.perform();
        try {
            script.execute();
        } catch(ExecutionError &e) {
            std::cerr << e.what() << std::endl;
            std::exit(1);
        }
    }


    std::vector<std::size_t> getFlags() {
        std::vector<std::size_t> indexes;
        
        for(std::size_t i = 0; i < arguments.size(); i++) {
            if(arguments[i][0] == '-') 
                indexes.push_back(i);
        }

        return indexes;
    }

}


}