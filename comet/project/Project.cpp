#include <project\project.hpp>

namespace comet {

Project::Project() { }


Project::Project(std::string name) {
    m_configurations.name = name;
}


Project::Project(Configs conf) : m_configurations(conf) { }

/*==================================Methods===================================*/

                    /*--------------Sources---------------*/

void Project::addSource(std::string file) {
    m_configurations.sources.push_back(file);
}

std::list<std::string> Project::getSources() {
    return m_configurations.sources;
}

void Project::addSourceDirectory(std::string dir) {
    m_configurations.sourceDirectories.push_back(dir);
}
    
std::list<std::string> Project::getSourceDirectories() {
    return m_configurations.sourceDirectories;
}

                    /*--------------Includes--------------*/

void Project::addIncludeDirectory(std::string dir) {
    m_configurations.includeDirectories.push_back(dir);
}

void Project::addIncludeDirectories(std::list<std::string> dirs) {
    m_configurations.includeDirectories.insert(
        m_configurations.includeDirectories.end(),
        dirs.begin(),
        dirs.end()
    );
}

std::list<std::string> Project::getIncludeDirectories() {
    return m_configurations.includeDirectories;
}

bool Project::hasIncludes() {
    return !m_configurations.includeDirectories.empty();
}

                        /*-----------Libraries------------*/

void Project::addLibarySearchingPath(std::string dir) {
    m_configurations.dllsDirectory.push_back(dir);
}

// Dynamic
void Project::addDL(std::string name) {
    m_configurations.dlls.push_back(name);
}


// Satic
void Project::addSL(std::string fullname) {
    m_configurations.sls.push_back(fullname);
}

std::list<std::string> &Project::getSLs() {
    return m_configurations.sls;
}

std::string Project::getName() {
    return m_configurations.name;
}
                    /*--------------Compiler-------------*/

void Project::setCompiler(std::string name, char standart) {
    m_configurations.compiler = name;
    if(standart <= 17) {
        m_configurations.standart = std::to_string((int)standart);
    } else {
        m_configurations.standart = "2b";
    }
}

std::string &Project::getCompiler() {
    return m_configurations.compiler;
}

std::string Project::getStandart() {
    return m_configurations.standart;
}

                    /*-------------Variables-------------*/

void Project::setVariable(std::string name, Value *val) {
    m_variables[name] = val;
}

Value *Project::getVaribale(std::string name) {
    return m_variables[name];
}

bool Project::contains(std::string name) {
    return m_variables.contains(name);
}


                    /*----------------Root---------------*/

void Project::setRoot(std::string root) {
    m_configurations.root = root;
}

std::string Project::getRoot() {
    return m_configurations.root;
}

                    /*------------Object path------------*/

// o-files path
bool Project::hasObjectsPath() {
    return !m_configurations.objectPath.empty();
}

void Project::setObjectPath(std::string path) {
    m_configurations.objectPath = path;
}

std::string Project::getObjectPath() {
    return m_configurations.objectPath;
}

void Project::addObjFile(std::string file) {
    m_configurations.objFiles.push_back(file);
}

std::list<std::string> Project::getObjFiles() {
    return m_configurations.objFiles;
}

                    /*------------Output path------------*/

// exe/dll-file path
bool Project::hasOutputPath() {
    return !m_configurations.resultPath.empty();
}

void Project::setOutputPath(std::string path) {
    m_configurations.resultPath = path;
}

std::string Project::getOutputPath() {
    return m_configurations.resultPath;
}


}