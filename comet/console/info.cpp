#include <console\console.hpp>

#include <project\project.hpp>
#include <project\managament.hpp>
#include <util.hpp>

#include <exception\console\CommandError.hpp>

#include <iostream>   // for info print
#include <chrono>     // for time information
#include <filesystem> // for special file info

#include <queue>
#include <set>

namespace comet {

namespace console {

    namespace chrono = std::chrono;

    namespace fs = std::filesystem;

    using namespace std::chrono_literals;

    // Global console variables
    extern std::list<std::string> arguments;
    
    extern Project *current;


    void printSources();

    void printIncludes();

    void printFilesTree(const fs::path &p, const std::string &tab = "");


    bool show_sources  = false;
    bool    full_names = false;
    

    bool shInclude     = false;
    bool    all_files  = false;
    bool    as_tree    = false;

    bool shRoot        = false; 

    bool shObjects     = false;

    void info() {
        std::string name;

        if(Projects::count() > 1) {
            name = arguments.front();
            
            if(!Projects::contains(name))
                throw UnknownProject(name); // project wasn't found
            
            arguments.pop_front();
            current = Projects::get(name);
        } else {
            current = Projects::target;
        }

        if(arguments.size() > 0) {
            for(auto arg : arguments) {
                if(arg.starts_with('-')) {
                    if(arg.compare("--full-names") == 0)
                        full_names = true;
                    if(arg.compare("--all-files") == 0)
                        all_files = true;
                    if(arg.compare("--as-tree") == 0)
                        as_tree = true;
                } else {
                    if(arg.compare("sources") == 0) 
                        show_sources = true;
                    else if(arg.compare("includes") == 0)
                        shInclude = true;
                    else if(arg.compare("root") == 0)
                        shRoot = true;
                    else if(arg.compare("objects") == 0)
                        shObjects = true;
                    // else {
                    //     name = arguments[i];
                    //     current = Projects::projects.at(name);
                    // }
                }
            }
        }

        
        
        if(show_sources) {
            printSources();
        }

        if(shInclude)
            printIncludes();


    }

    /*Info command support functions*/

    
    void printSources() {
        std::cout << "Project " << current->getName() 
                    << " contains these sources:\n";
        fs::directory_entry entry;
        if(as_tree) {
            fs::path tmp;
            for(const auto &dir : current->getSourceDirectories()) {
                printFilesTree(tmp.assign(dir));
            }
        } else if(!full_names) {
            auto filesTable = current->getFilesTable();
            for(auto pair : filesTable) {
                entry.assign(pair.second); // sets file

                if(fs::exists(entry)) {
                    // Getting time of last edited
                    auto lastEdited = chrono::current_zone()->to_local(
                        chrono::clock_cast<chrono::system_clock>
                                    (entry.last_write_time())
                        );
                    // File time
                    std::cout <<
                    std::format(
                        "{:%d.%m.%Y  %T}\t", 
                            chrono::floor<chrono::seconds>(lastEdited)
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
                    auto lastEdited = chrono::current_zone()->to_local(
                                        chrono::clock_cast<chrono::system_clock>
                                                    (entry.last_write_time())
                                        );
                    // File time
                    std::cout <<
                    std::format(
                        "{:%Y-%m-%d  %T}\t", 
                            chrono::floor<chrono::seconds>(lastEdited)
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


    void printIncludes() {
        std::cout << "Project " << current->getName();
        if(all_files) {
            std::cout << " includes these files" << std::endl;
        } else {
            std::cout << " includes these directories" << std::endl;
            std::cout << "Date        Time       Name" << std::endl;
        }


        if(as_tree) {
            printFilesTree("include");
        } else if(all_files) {
            auto includeDirectories = current->getIncludeDirectories();
            for(const auto &dir : includeDirectories) {
                auto files = getFiles(dir);
                std::cout << "Direcotry <" << dir << ">:\n";
                std::cout << "Date        Time      Size       Name" << std::endl;
                for(const auto &file : files) {
                    auto lastEdited =  chrono::current_zone()->to_local(
                                            chrono::clock_cast<chrono::system_clock>
                                                    (fs::last_write_time(file))
                                        );

                    // File time
                    std::cout <<
                    std::format(
                        "{:%d.%m.%Y  %T}\t", 
                            chrono::floor<chrono::seconds>(lastEdited)
                        );
                    
                    // File size
                    std::cout.width(8);
                    std::cout << getSeparatedNumber(fs::file_size(file));

                    // File name
                    std::cout << ' ' << file.filename().string() << std::endl;
                }
            }
        } else {
            auto includeDirectories = current->getIncludeDirectories();
            for(const auto &dir : includeDirectories) {
                fs::directory_entry file(dir);
                auto lastEdited = chrono::clock_cast<chrono::system_clock>
                                                    (fs::last_write_time(file));
                // File time
                std::cout <<
                std::format(
                    "{:%d.%m.%Y  %T}\t", 
                        chrono::floor<chrono::seconds>(lastEdited + 3h)
                    );
                
                std::cout << ' ' << dir << std::endl;
            }
        }
    }



    void printFilesTree(const fs::path &p, const std::string &tab) {
        std::cout << tab << "v " << p.stem().string() << std::endl;
        for(const auto& entry : fs::directory_iterator(p)) {
            if(fs::is_directory(entry)) {
                printFilesTree(entry.path(), tab + " ");
                continue;
            }
            std::cout << tab << "  > " << entry.path().filename().string() << std::endl;
        }    
        
    }
}



}