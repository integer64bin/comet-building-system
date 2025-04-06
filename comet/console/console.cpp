#include <console\console.hpp>

#include <iostream> // condole output
#include <fstream>  // file reading/writing

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
    std::string workspace = ".";

    // List of arguments
    std::list<std::string> arguments;

    // Current project
    Project *current;


    
    
    void parseArguments(int argc, const char **argv) {
        if(argc == 1) {
            return;
        }

        arguments = makeStringList(argc, argv);
        arguments.pop_front(); // deletes comet.exe

        try {
            // Command pipeline
            parseCommand();
        } catch(ConsoleError &e) {
            std::cerr << "An error occured during command execution..." << std::endl;
            std::cerr << e.what() << std::endl;
            std::exit(1); 
        }
    }

    bool terminal_mode = false;

    void parseCommand(std::string command) {
        std::size_t lastSpace = 0;
        std::size_t space = command.find(' ');
        arguments.clear();
        for(;;) {
            arguments.push_back(command.substr(lastSpace, space-lastSpace));
            lastSpace = space + 1;
            while(command.at(lastSpace) == ' ') lastSpace++;
            space = command.find(' ', lastSpace);
            if(space == command.npos || space >= command.size()) {
                arguments.push_back(command.substr(lastSpace));
                break;
            }
        }
        parseCommand();
    }

    void parseCommand() {
        // Count of arguments without command and work directory
        int argc = 1;

        std::string command = arguments.front();
        arguments.pop_front();  // deletes command

        if(command.compare("init") == 0) {
            // fs::path dir;
            // init(dir);
        
        } else if(command.compare("terminal") == 0) {
            terminal_mode = true;
            terminal();
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

}


}