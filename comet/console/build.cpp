#define CONSOLE_IMPLEMENTATION

#include <console\console.hpp>

#include <project\project.hpp>
#include <project\managament.hpp>
#include <project\compiler.hpp>

#include <iostream>

#include <exception\console\CommandError.hpp>

namespace comet {

namespace console {

    // Global console variables
    extern std::list<std::string> arguments;
    
    extern Project *current;

    namespace fs = std::filesystem;

    /*==========================Methods declarations==========================*/

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

    /**
     * @brief If directories for object files doesn't exist creates them. 
     * Also fills a list of the object files of the current project  
     * 
     * @param objDirectory 
     */
    void initObjDirectories(std::string objDirectory);

    /**
     * @brief Builds program from source files without compilation
     * 
     */
    void buildFromSource();

    /**
     * Variables below are spectial build flags
     */
    // If files specified by flag "-f" it equals true
    bool selective_compilation;

    // If programm has flag "-r" it equals true
    bool run_after;
    
    void build() {
        std::string name = arguments.front().starts_with('-') ? 
                            "" :
                            arguments.front();


        // build flags parsing

        // Files specified by "f" flag
        std::list<std::string> selectedFiles;

        // Arguments specified by "r" falg
        std::string startArgs;

        for(auto argument : arguments) {
            if(argument.starts_with("-f")) {
                selective_compilation = true;
                // Two cases:
                // 1) One file: -ffile
                // 2) N files: -ffile0,fil1,...,filen
                std::string names = argument.substr(2);
                // case 1
                if(names.find(',') == names.npos){
                    selectedFiles.push_back(names);
                } else { // case 2
                    int lastComma = 0;
                    // Adding a first file
                    int comma = names.find(',', lastComma+1);
                    std::string name = names.substr(0, comma);
                    selectedFiles.push_back(name);
                    for(;;) {

                        lastComma = comma;
                        comma = names.find(',', lastComma+1);
                        
                        int count = comma == names.npos ? 
                                    names.size()-lastComma-1 :
                                    comma-lastComma-1;
                        
                        name = names.substr(lastComma+1, comma-lastComma-1);
                        
                        selectedFiles.push_back(name);

                        if(comma == names.npos)
                            break;
                    }
                }
            } else if(argument.compare("--debug-info") == 0) { 
                Compiler::debug_info = true;
            } else if(argument.compare("--ignore-errors") == 0) {
                Compiler::ignore_errors = true;
            } else if(argument.starts_with("-r")) {
                std::string startArgsList = argument.substr(3);
                // Two cases
                // 1) One argument: -r--arg0
                // 2) N arguments: -r-o,-f,-s,--aeg0...
                
                // case 1
                if(startArgsList.find(',') == startArgsList.npos) {
                    startArgs = std::move(startArgsList);
                } else { // case 2
                    int lastComma = 0;
                    // Adding a first file
                    int comma = startArgsList.find(',', lastComma+1);
                    std::string arg = startArgsList.substr(0, comma);
                    startArgs.append(arg).push_back(' ');
                    for(;;) {
                        lastComma = comma;
                        comma = startArgsList.find(',', lastComma);
                        
                        int count = comma == startArgsList.npos ? 
                                    startArgsList.size()-lastComma-1 :
                                    comma-lastComma-1;
                        
                        arg = startArgsList.substr(lastComma+1, count);

                        startArgs.append(arg).push_back(' ');

                        lastComma = comma;
                        if(comma == startArgsList.npos)
                            break;
                    }
                }
            }
        }

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
                
                Compiler::compile(opts, sources.back(), objects.back());
    
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

    

    std::string getStandartFlag(Project *target) {
        std::string s = "-std=c++";

        s += target->getStandart();

        return s;
    }

}

}