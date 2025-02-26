#include <console\console.hpp>

#include <iostream> // condole output
#include <fstream>  // file reading/writing

#include <util.hpp>
#include <project\project.hpp>

#include <Script.hpp>

#include <exception\console\CommandError.hpp>

namespace comet {

namespace console {

    namespace fs = std::filesystem;

    // Place from which called comet.exe
    //
    std::string workspace;

    //  
    std::string root = ".";

    // List of arguments
    std::vector<std::string> arguments;

    // Current project
    Project *current;

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

        parseCommand();
    }

    void parseCommand() {
        // Count of arguments without command and work directory
        int argc = arguments.size() - 2;

        std::string command = arguments[1];

        if(command.compare("setup") == 0) {
            fs::path dir;
            if(argc == 0 || (argc == 1 && arguments[2].compare("."))) {
                dir = fs::path(workspace);
            } else {
                dir = fs::path(workspace + "\\" + arguments[2]);
            }

            setup(dir);

         
        } else if(command.compare("help") == 0) {
            
        } else { // commands that require script
            readScript();
            
            if(command.compare("build") == 0) {
                if(argc == 0) {
                    build("");             
                } else
                    build(arguments[2]);
            } else if(command.compare("link") == 0) {

            } else if(command.compare("info") == 0) {

            }
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
        // If file exists do nothing
        if(fs::exists(where))
            return;
        // Else
        // Opening the file in append mode
        // and adding commet
        std::ofstream xconfigFile(where, std::ios_base::app);
        xconfigFile << "# Write your script here..." << std::endl;
        
        xconfigFile.close();
    }

    
    void build(std::string name) {
        if(name.empty()) {
            if(!Projects::projects.empty() && Projects::projects.size() > 1) {
                throw CommandError();
            }

            name = Projects::target->getName();

            std::cout << "Starting to build project " <<
                    Projects::target->getName() << std::endl;


            if(Projects::target->hasObjectsPath())
                buildWithObjFiles(Projects::target);
            else 
                buildFromSource(Projects::target);

        }
    }



    void parseBuildFlags() {
        std::vector<int> indexes = getFlags();

        for(int i : indexes) {
            if(arguments[i].starts_with("-f")) {

                std::string names = arguments[i].substr(3);


                int lastComma;
                for(;;) {
                    int comma = names.find(',', lastComma);
                    if(comma == names.npos)
                        break;
                    
                    std::string name = names.substr(0, comma);

                    lastComma = comma;
                }

            }
        }
    }

    // First compiles all file
    // After links them together
    void buildWithObjFiles(Project *t) {

        std::string out = t->getObjectPath() + "\\";
        // Creates output directories, if they doesn't exist
        // Also adds object files to Project::m_configurations.objFiles
        initObjDirectories(t, out);
        
        // Specifies c++ standart
        std::string stdFlag = getStandartFlag(t);


        CompilerOptions opts {
            t->getCompiler(),
            Compiler::getFlags({stdFlag, "-pipe"}),
            t->getRoot(),
            t->getIncludeDirectories(),
            t->getLibarySearchingPaths(),
            t->getLibraries()
        };

        auto objects = t->getObjFiles();
        auto sources = t->getSources();
        
        while(objects.size() > 0) {
            
            Compiler::compile(opts, objects.back(), sources.back());

            objects.pop_back();
            sources.pop_back();

            t->getObjFile("");

        }


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
    
    void buildFromSource(Project *target) {

    }



    std::vector<int> getFlags() {
        std::vector<int> indexes;
        
        for(int i = 0; i < arguments.size(); i++) {
            if(arguments[i][0] == '-') 
                indexes.push_back(i);
        }

        return indexes;
    }


    std::string getStandartFlag(Project *target) {
        std::string s = "-std=c++";

        s += target->getStandart();

        return s;
    }

    

}


}