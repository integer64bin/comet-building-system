#include <iostream>

#include <filesystem>

#include <project\project.hpp>
#include <project\sys\system.hpp>

namespace comet {

namespace fs = std::filesystem;

/*===============================Main varibales==============================*/

std::map<std::string, Project*> Projects::projects;

Project *Projects::target;

/*==========================Functions implementation=========================*/

Project &project(std::string name) {
    Project *newProj = new Project;

    // Adds new projetcs to projects list
    Projects::projects.emplace(name, newProj);

    Projects::target = newProj;

    return *newProj;
}


void setCompiler(std::string c, char standart) {
    Projects::target->setCompiler(c, standart);
}

                    /*---------------Sourecs--------------*/

void addSourcesPath(std::vector< std::string > paths) {
    for(auto p : paths) {
        addSourcePath(p);
    }
}

void addSourcePath(std::string path) {
    for(const auto &entry : fs::directory_iterator(path)) {
        if(fs::is_directory(entry)) {
            addSourceDirectory(entry.path().string());
            addSourcePath(entry.path().string());
            continue;
        }
        if(entry.path().extension() == ".cpp")
            addSource( entry.path().string() );
    }
}

void addSource(std::vector< std::string > files) {
    for(auto f : files) {
        addSource(f);
    }
}

void addSource(std::string file) {
    Projects::target->addSource(file);
}

std::list<std::string> getSources() {
    return Projects::target->getSources();
}

void addSourceDirectory(std::string dir) {
    Projects::target->addSourceDirectory(dir);
}

std::list<std::string> getSourceDirectories() {
    return Projects::target->getSources();
}

                    /*---------------Include--------------*/

void addInclude(std::string s) {
    Projects::target->addIncludeDirectory(s);
}

std::list<std::string> getIcludes() {
    return Projects::target->getIncludeDirectories();
}


void setVariable(std::string name, Value *val) {
    Projects::target->setVariable(name, val);
}

Value *getVariable(std::string name) {
    return Projects::target->getVaribale(name);
}

                    /*-----Root, object & output paths----*/

// .o-files
void setObjectPath(std::string path) {
    Projects::target->setObjectPath(path);
}


std::string getObjectPath() {
    return Projects::target->getObjectPath();
}

// exe/dll
void setOutputPath(std::string path) {
    Projects::target->setOutputPath(path);
}


std::string getOutputPath() {
    return Projects::target->getOutputPath();
}

// Root
void setRoot(std::string path) {
    Projects::target->setRoot(path);
}

std::string getRoot() {
    return Projects::target->getRoot();
}

/*==========================Script functions parsing==========================*/

void callByName(std::string funcName, std::vector<Value *> arguments) {
    if(funcName.compare("project") == 0) {
        Project *newProj = new Project(arguments[0]->asString());

        // Add to projects' table
        Projects::projects.emplace(arguments[0]->asString(), newProj);
        
        // Set target
        Projects::target = newProj;
    } else if(funcName.compare("setCompiler") == 0) {
        setCompiler(arguments[0]->asString(),
                    (char)arguments[1]->asNumber());
    } else if(funcName.compare("setRoot") == 0) {
        setRoot(arguments[0]->asString());
    } else if(funcName.compare("addSourcesPath") == 0) {
        addSourcePath(arguments[0]->asString());
    } else if(funcName.compare("addIncludes") == 0) {
        for(auto i : arguments)
            addInclude(i->asString());
    } else if(funcName.compare("setOutPath") == 0) {
        setObjectPath(arguments[0]->asString());
    } else if(funcName.compare("setExecutablePath") == 0) {
        setOutputPath(arguments[0]->asString());
    }
}

int Projects::run(const std::string &name, const std::string &arguments) {
    return 10;
}

void Projects::init() {
    comet::system::init();
}

void Projects::finalize() {
    comet::system::finalize();
    for(auto proj : projects) {
        delete proj.second;
    }
}


}