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

            setup(dir);

         
        } else if(command.compare("help") == 0) {
            
        } else { // commands that require script
            readScript();
            if(command.compare("build") == 0) {
                build();
            } else if(command.compare("link") == 0) {

            } else if(command.compare("info") == 0) {

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

    
    /**
     * Variables below are spectial build flags
     */
    // 
    bool selective_compilation;

    bool run_after;
    
    void build() {
        // First step falgs parsing
        std::vector<std::size_t> indexes = getFlags();

        // build flags parsing

        // Files specified by "f" flag
        std::list<std::string> selectedFiles;

        // Arguments specified by "r" falg
        std::string startArgs;

        for(std::size_t i : indexes) {
            if(arguments[i].starts_with("-f")) {
                selective_compilation = true;
                // Two cases:
                // 1) One file: -ffile
                // 2) N files: -ffile0,fil1,...,filen
                std::string names = arguments[i].substr(2);
                // case 1
                if(names.find(',') == names.npos){
                    selectedFiles.push_back(names);
                } else { // case 2
                    int lastComma;
                    for(;;) {
                        int comma = names.find(',', lastComma);
                        if(comma == names.npos)
                            break;
                        
                        std::string name = names.substr(0, comma);
                        
                        selectedFiles.push_back(name);

                        lastComma = comma;
                    }
                }
            } else if(arguments[i].compare("--debug-info") == 0) { 
                Compiler::debug_info = true;
            } else if(arguments[i].compare("--ignore-errors") == 0) {
                Compiler::ignore_errors = true;
            } else if(arguments[i].starts_with("-r")) {
                std::string startArgsList = arguments[i].substr(3);
                // Two cases
                // 1) One argument: -r--arg0
                // 2) N arguments: -r-o,-f,-s,--aeg0...
                
                // case 1
                if(startArgsList.find(',') == startArgsList.npos) {
                    startArgs = std::move(startArgsList);
                } else { // case 2
                    int lastComma;
                    for(;;) {
                        int comma = startArgsList.find(',', lastComma);
                        if(comma == startArgsList.npos)
                            break;
                        
                        std::string arg = startArgsList.substr(0, comma);

                        startArgs.append(arg).push_back(' ');

                        lastComma = comma;
                    }
                }
            }
        }
        
        std::string name = arguments[2].starts_with("-") ? 
                                    "" : arguments[2];

        // Building 
        if(name.empty()) {
            if(!Projects::projects.empty() && Projects::projects.size() > 1) {
                throw InvalidArgument(
                    "Configuration file provides more than one project\n"
                    "Wasn't specified name of project"
                );
            }

            
            name = Projects::target->getName();
            current = Projects::target;
        } else {
            if(!Projects::projects.contains(name)) {}
                throw UnknownProject(name);
            current = Projects::projects.at(name);
            name = current->getName();
        }
        
        std::cout << "Starting to build project " << name << std::endl;

        if(selective_compilation) {
            buildWithObjFiles(selectedFiles);
        } else if(current->hasObjectsPath())
            buildWithObjFiles();
        else 
            buildFromSource();

        if(run_after && Compiler::erros_count == 0) {
            Projects::run(name, startArgs);
        }

    }



    void buildWithObjFiles(std::list<std::string> names) {
        std::string out = current->getObjectPath() + "\\";
        // Creates output directories, if they doesn't exist
        // Also adds object files to Project::m_configurations.objFiles
        initObjDirectories(out);
        
        // Specifies c++ standart
        std::string stdFlag = getStandartFlag(current);


        CompilerOptions opts {
            current->getCompiler(),
            Compiler::getFlags({stdFlag, "-pipe"}),
            current->getRoot(),
            current->getIncludeDirectories(),
            current->getLibarySearchingPaths(),
            current->getLibraries()
        };

        // Compilation
        if(names.empty()) {
            auto objects = current->getObjFiles();
            auto sources = current->getSources();
            
            while(objects.size() > 0) {
                
                Compiler::compile(opts, objects.back(), sources.back());
    
                objects.pop_back();
                sources.pop_back();
    
            }
        } else { // -f...
            for(auto name : names) {
                std::string src = current->getSource(name);
                std::string obj = current->getObjFile(name);

                Compiler::compile(opts, src, obj);
            }
        }

        // Linking
        Compiler::link(opts, current->getObjFiles());

    }

    
    
    void initObjDirectories(std::string objDirectory) {
        auto directories = current->getSourceDirectories();
        
        // creating output directories
        for(auto entry : directories) {
            entry.insert(0, objDirectory);
            fs::directory_entry dir = fs::directory_entry(fs::path(entry));
            if(!dir.exists()) {
                fs::create_directories(dir.path());
            }
        }

        auto sources = current->getSources();

        for(auto objFile : sources) {
            objFile.insert(0, objDirectory);
            objFile.replace(objFile.length()-3, 3, "o");
            
            current->addObjFile( objFile );
        }
    }
    
    void buildFromSource() {

    }



    std::vector<std::size_t> getFlags() {
        std::vector<std::size_t> indexes;
        
        for(std::size_t i = 0; i < arguments.size(); i++) {
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