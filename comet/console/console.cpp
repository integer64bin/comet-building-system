#include <console\console.hpp>

#include <iostream>
#include <fstream>

#include <util.hpp>
#include <project\project.hpp>

#include <Script.hpp>

namespace comet {

namespace console {

    namespace fs = std::filesystem;

    std::string workspace;

    std::string root = ".";

    std::string getWorkingDirectory(std::string &line) {
        auto i = line.size() - 1;
        for(; i >= 0; i--) {
            if(line[i] == '\\')
                break;
        }
        return line.substr(0, i);
    }
    
    void parseArguments(int argc, const char **argv) {

        if(argc == 0) {
            std::cout << "" << std::endl;
            return;
        }

        std::string *args = makeStringArray(argc, argv);

        // after last '\' comes exe-file name
        // befor last '\' comes working directory
        workspace = getWorkingDirectory(args[0]);

        parseCommand(args[1], &args[2], argc-2);

        delete[] args;
    }

    void parseCommand(std::string command, std::string *args, int argc) {
        if(command.compare("setup") == 0) {
            fs::path dir;
            if(argc == 0 || (argc == 1 && args[0].compare("."))) {
                // std::ofstream xconfigFile(".");
                dir = fs::path(workspace);
            } else {
                dir = fs::path(workspace + "\\" + args[0]);
            }

            setup(dir);

        } else if(command.compare("build") == 0) {
            readScript();
            if(argc == 0) {
                build("");             
            } else
                build(args[0]);
        }
    }



    void readScript() {
        Script script(workspace + "\\.xconfig");

        script.perform();

        script.execute();
    }


    /*============================Console command============================*/

    
    void setup(fs::path where) {
        where.append("\\.xconfig");
        std::ofstream xconfigFile(where, std::ios_base::app);
        xconfigFile << "# Write your script here..." << std::endl;
        xconfigFile.close();
    }

    
    void build(std::string name) {
        if(name.empty()) {
            if(!Projects::projects.empty() && Projects::projects.size() > 1) {
                std::cerr << "Enter target name" << std::endl;
                std::cerr << "Script is interrupted" << std::endl;
                exit(1);
            }

            name = Projects::target->getName();

            std::cout << "Starting to build project " <<
                    Projects::target->getName() << std::endl;


            if(Projects::target->hasObjectsPath())
                _buildWithObjFiles(Projects::target);
            else 
                _buildFromSource(Projects::target);

        }
    }

    void _buildWithObjFiles(Project *t) {

        std::string out = t->getObjectPath() + "\\";
        initObjDirectories(t, out);
        
        std::string options;

        // Creates -I flag for include directories
        if(t->hasIncludes()) {
            std::list<std::string> includes = t->getIncludeDirectories();

            std::string inclFlag = std::move(getIncludeFlags(t));

            options.append(inclFlag);
        }

        // Specifies c++ standart
        std::string stdFlag = getStandartFlag(t);

        options.append(stdFlag);
        options.push_back(' ');


        // Starting compilation
        // Objects iters
        auto objects = t->getObjFiles();
        auto sources = t->getSources();
        while(objects.size() > 0) {
            std::cout << objects.back() << ' ' << sources.back() << std::endl;

            objects.pop_back();
            sources.pop_back();
        }


    }


    void _buildFromSource(Project *target) {

    }

    // returns list of directories
    std::set<std::string> getDirectories(std::list<std::string> files) {
        std::set<std::string> directories;

        for(auto file : files) {
            directories.emplace(getWorkingDirectory(file));
        }

        return directories;
    }

    void initObjDirectories(Project *t, std::string objDirectory) {
        auto directories = t->getSourceDirectories();
        
        // creating output directories
        for(auto entry : directories) {
            entry.insert(0, objDirectory);
            fs::directory_entry dir = fs::directory_entry(fs::path(entry));
            if(!dir.exists()) {
                fs::create_directories(dir.path());
            }
        }

        auto sources = t->getSources();

        for(auto objFile : sources) {
            objFile.insert(0, objDirectory);
            objFile.replace(objFile.length()-3, 3, "o");

            t->addObjFile( objFile );
        }
    }

    // include supprot
    std::string getIncludeFlags(Project *target) {
        std::string inclFlag;
        const std::list<std::string> &includes = target->getIncludeDirectories();
        for(auto includeDirectory : includes) {
            inclFlag.append("-I\"")
                    .append(target->getObjectPath())
                    .append("\\")
                    .append(includeDirectory)
                    .append("\" ");
        }
        return inclFlag;
    }

    std::string getStandartFlag(Project *target) {
        std::string s = "-std=c++";

        s += target->getStandart();

        return s;
    }

    

}


}