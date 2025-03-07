#include <console\console.hpp>

#include <project\project.hpp>
#include <util.hpp>

#include <iostream>   // for info print
#include <chrono>     // for time information
#include <filesystem> // for special file info

namespace comet {

namespace console {

    namespace chrono = std::chrono;

    namespace fs = std::filesystem;

    using namespace std::chrono_literals;

    // Global console variables
    extern std::vector<std::string> arguments;
    
    extern Project *current;

    bool show_sources  = false;
    bool    full_names = false;
    

    bool shInclude     = false;
    bool    all_files  = false;

    bool shRoot    = false; 

    void info() {
        std::vector<std::size_t> indexes = getFlags();

        std::string name;

        if(arguments.size() > 2) {
            for(int i = 2; i < arguments.size(); i++) {
                if(arguments[i].starts_with('-')) {
                    if(arguments[i].compare("--full-names") == 0)
                        full_names = true;
                    if(arguments[i].compare("--all-files") == 0)
                        all_files = true;
                } else {
                    if(arguments[i].compare("sources") == 0) 
                        show_sources = true;
                    else if(arguments[i].compare("includes") == 0)
                        shInclude = true;
                    else if(arguments[i].compare("root") == 0)
                        shRoot = true;
                    // else {
                    //     name = arguments[i];
                    //     current = Projects::projects.at(name);
                    // }
                }
            }
        }

        current = Projects::target;
        
        if(show_sources) {
            printSources(full_names);
        }




    }

    /*Info command support functions*/

    
    void printSources(bool full_names) {
        std::cout << "Sources:\n";
        fs::directory_entry entry;
        if(!full_names) {
            auto filesTable = current->getFilesTable();
            for(auto pair : filesTable) {
                entry.assign(pair.second); // sets file

                if(fs::exists(entry)) {
                    // Getting time of last edited
                    auto lastEdited = chrono::clock_cast<chrono::system_clock>
                                                    (entry.last_write_time());
                    // File time
                    std::cout <<
                    std::format(
                        "{:%d.%m.%Y  %T}\t", 
                            chrono::floor<chrono::seconds>(lastEdited + 3h)
                        );

                    std::cout.width(8);
                    std::cout << getSeparatedNumber(fs::file_size(entry));

                    std::cout << ' ' << pair.first << '\n';
                }
            }
            std::cout.width(15);
            std::cout << filesTable.size() << " files" << std::endl;
        } else {
            auto files = current->getSources();
            for(auto file : files) {
                if(fs::exists(file)) {
                    entry.assign(file);
                    // Getting time of last edited
                    auto lastEdited = chrono::clock_cast<chrono::system_clock>
                                                    (entry.last_write_time());
                    // File time
                    std::cout <<
                    std::format(
                        "{:%Y-%m-%d  %T}\t", 
                            chrono::floor<chrono::seconds>(lastEdited + 3h)
                        );
                    std::cout.width(8);
                    std::cout << getSeparatedNumber(fs::file_size(file));

                    std::cout << ' ' << file << '\n';
                }
            }
            std::cout.width(15);
            std::cout << files.size() << " files" << std::endl;
        }
    }


}

}