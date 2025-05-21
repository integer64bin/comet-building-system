#include <iostream>

#include <filesystem>

#include <project\managament.hpp>
#include <project\project.hpp>
#include <project\sys\system.hpp>

#include <exception\execution\UnknownFunction.hpp>
#include <exception\console\CommandError.hpp>

#include <project\function.hpp>
#include <functional>

namespace comet {


namespace fs = std::filesystem;

/*===============================Main varibales==============================*/

std::map<std::string, std::function<void(Project*, std::vector<Value*>)> > Projects::functions;

std::map<std::string, Project*> Projects::projects;

Project *Projects::target;


/*==========================Script functions parsing==========================*/

void Projects::call(const std::string &name, const std::vector<Value*> &arguments) {
    try {
        functions.at(name)(target, arguments);
    } catch(std::out_of_range) {
        throw UnknownFunction(name);
    }
}

void Projects::initProject(std::string name, int version) {
    Project *newProj = new Project(name);

        // Add to projects' table
    Projects::projects.emplace(name, newProj);
    
    // Set target
    Projects::target = newProj;
}

int Projects::run(const std::string &name, const std::string &arguments) {
    return 10;
}


int Projects::count() {
    return projects.size();
}

bool Projects::contains(const std::string &name) {
    return projects.contains(name);
}

Project *Projects::get(const std::string &name) {
    try {
        return projects.at(name);
    } catch (std::out_of_range) {
        throw UnknownProject(name);
    }
}

// Initialization
void Projects::init() {
    // Fucntions initialization
    functions.emplace(
        functions::F_PROJECT,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void  {
            Project *newProj = new Project(arguments[0]->asString());

            // Add to projects' table
            Projects::projects.emplace(arguments[0]->asString(), newProj);
            
            // Set target
            Projects::target = newProj;
        }
    );

    functions.emplace(
        functions::F_SET_ROOT,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            target->setRoot(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_COMPILER,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            target->setCompiler(arguments[0]->asString(),
                    (char)arguments[1]->asNumber());
        }
    );

    functions.emplace(
        functions::F_ADD_INCLUDES,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            for(auto i : arguments)
                target->addIncludeDirectory(i->asString());
        }
    );

    functions.emplace(
        functions::F_ADD_SOURCES_PATH,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            target->addSourcesFrom(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_OUT_PATH,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            target->setObjectPath(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_EXECUTABLE_PATH,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            target->setOutputPath(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_SET_EXECUTABLE,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            target->setOutput(arguments[0]->asString());
        }
    );

    functions.emplace(
        functions::F_ADD_LIBRARIES,
        [&](Project *target, std::vector<Value *> arguments) mutable -> void {
            for(auto lib : arguments) {
                target->addLibrary(lib->asString());
            }
        }
    );

}


void Projects::finalize() {
    for(auto proj : projects) {
        delete proj.second;
    }
}


}