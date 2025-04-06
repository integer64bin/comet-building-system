#include <iostream>

#include <filesystem>

#include <project\managament.hpp>
#include <project\project.hpp>
#include <project\sys\system.hpp>

#include <exception\execution\UnknownFunction.hpp>

#include <project\function.hpp>
#include <functional>

namespace comet {


namespace fs = std::filesystem;

/*===============================Main varibales==============================*/

std::map<std::string, std::function<void(std::vector<Value*>)> > Projects::functions;

std::map<std::string, Project*> Projects::projects;

Project *Projects::target;


/*==========================Script functions parsing==========================*/

void callByName(std::string funcName, std::vector<Value *> arguments) {
    // if(funcName.compare("project") == 0) {
    //     Project *newProj = new Project(arguments[0]->asString());

    //     // Add to projects' table
    //     Projects::projects.emplace(arguments[0]->asString(), newProj);
        
    //     // Set target
    //     Projects::target = newProj;
    // } else if(funcName.compare("setCompiler") == 0) {
    //     Projects::target->setCompiler(arguments[0]->asString(),
    //                 (char)arguments[1]->asNumber());
    // } else if(funcName.compare("setRoot") == 0) {
    //     Projects::target->setRoot(arguments[0]->asString());
    // } else if(funcName.compare("addSourcesPath") == 0) {
    //     Projects::target->addSourcesFrom(arguments[0]->asString());
    // } else if(funcName.compare("addIncludes") == 0) {
    //     for(auto i : arguments)
    //         Projects::target->addIncludeDirectory(i->asString());
    // } else if(funcName.compare("setOutPath") == 0) {
    //     Projects::target->setObjectPath(arguments[0]->asString());
    // } else if(funcName.compare("setExecutablePath") == 0) {
    //     Projects::target->setOutputPath(arguments[0]->asString());
    // } else if(funcName.compare("setExecutable") == 0) {
    //     // setOutput(arguments[0]->asString());
    // }
}


void Projects::call(const std::string &name, const std::vector<Value*> &arguments) {
    try {
        functions.at(name)(arguments);
    } catch(std::out_of_range) {
        throw UnknownFunction(name);
    }
}


int Projects::run(const std::string &name, const std::string &arguments) {
    return 10;
}

void Projects::init() {
    // Fucntions initialization
    functions.emplace(
        functions::F_PROJECT,
        [&](std::vector<Value *> arguments) mutable -> void  {
            Project *newProj = new Project(arguments[0]->asString());

            // Add to projects' table
            Projects::projects.emplace(arguments[0]->asString(), newProj);
            
            // Set target
            Projects::target = newProj;
        }
    );

    functions.emplace(
        functions::F_SET_ROOT,
        [&](std::vector<Value *> arguments) mutable -> void {
            Projects::target->setRoot(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_COMPILER,
        [&](std::vector<Value *> arguments) mutable -> void {
            Projects::target->setCompiler(arguments[0]->asString(),
                    (char)arguments[1]->asNumber());
        }
    );

    functions.emplace(
        functions::F_ADD_INCLUDES,
        [&](std::vector<Value *> arguments) mutable -> void {
            for(auto i : arguments)
                Projects::target->addIncludeDirectory(i->asString());
        }
    );

    functions.emplace(
        functions::F_ADD_SOURCES_PATH,
        [&](std::vector<Value *> arguments) mutable -> void {
            Projects::target->addSourcesFrom(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_OUT_PATH,
        [&](std::vector<Value *> arguments) mutable -> void {
            Projects::target->setObjectPath(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_EXECUTABLE_PATH,
        [&](std::vector<Value *> arguments) mutable -> void {
            Projects::target->setOutputPath(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_EXECUTABLE,
        [&](std::vector<Value *> arguments) mutable -> void {
            Projects::target->setOutput(arguments[0]->asString());
        }
    );

}

void Projects::finalize() {
    for(auto proj : projects) {
        delete proj.second;
    }
}


}