#include <iostream>

#include <filesystem>

#include <project\managament.hpp>
#include <project\project.hpp>
#include <project\sys\system.hpp>

namespace comet {


namespace fs = std::filesystem;

/*===============================Main varibales==============================*/

std::map<std::string, Project*> Projects::projects;

Project *Projects::target;


/*==========================Script functions parsing==========================*/

void callByName(std::string funcName, std::vector<Value *> arguments) {
    if(funcName.compare("project") == 0) {
        Project *newProj = new Project(arguments[0]->asString());

        // Add to projects' table
        Projects::projects.emplace(arguments[0]->asString(), newProj);
        
        // Set target
        Projects::target = newProj;
    } else if(funcName.compare("setCompiler") == 0) {
        Projects::target->setCompiler(arguments[0]->asString(),
                    (char)arguments[1]->asNumber());
    } else if(funcName.compare("setRoot") == 0) {
        Projects::target->setRoot(arguments[0]->asString());
    } else if(funcName.compare("addSourcesPath") == 0) {
        Projects::target->addSourcesFrom(arguments[0]->asString());
    } else if(funcName.compare("addIncludes") == 0) {
        for(auto i : arguments)
            Projects::target->addIncludeDirectory(i->asString());
    } else if(funcName.compare("setOutPath") == 0) {
        Projects::target->setObjectPath(arguments[0]->asString());
    } else if(funcName.compare("setExecutablePath") == 0) {
        Projects::target->setOutputPath(arguments[0]->asString());
    } else if(funcName.compare("setExecutable") == 0) {
        // setOutput(arguments[0]->asString());
    }
}

int Projects::run(const std::string &name, const std::string &arguments) {
    return 10;
}

void Projects::init() {
    
}

void Projects::finalize() {
    for(auto proj : projects) {
        delete proj.second;
    }
}


}