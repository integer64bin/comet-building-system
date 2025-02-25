#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>

#include <ast\value\Value.hpp>

#include <project\compiler.hpp>

namespace comet {

struct Configs {
    // Name of project
    std::string name = "noname";

    std::string root = ".";

    // Compiler that 
    std::string compiler = "g++";

    std::string standart;

    // List of all source files
    // with full path
    std::list<std::string> sources;

    std::list<std::string> sourceDirectories;

    std::list<std::string> objFiles;

    std::list<std::string> objDirectories;

    // List of include directories
    std::list<std::string> includeDirectories;

    // Path to object files 
    std::string objectPath = "";

    // Path to executable/library 
    std::string resultPath = "";

    // directories which contains libraries
    std::list<std::string> dllsDirectory;

    // libraries which need to link
    std::list<std::string> dlls;

    // libraries which need to link
    // List of files' names with full path
    std::list<std::string> sls;

};



class Project {


    friend class Compiler;

    std::map<std::string, Value *> m_variables;

    // std::map<std::string, Value *> m_constants;

    Configs m_configurations;


public:

    Project();

    Project(std::string name);

    Project(Configs conf);

    /*================================Methods=================================*/

                      /*--------------Sources---------------*/
    
    void addSource(std::string file);

    std::list<std::string> getSources();
    
    void addSourceDirectory(std::string dir);
    
    std::list<std::string> getSourceDirectories();

                      /*--------------Includes--------------*/
    
    void addIncludeDirectory(std::string dir);

    void addIncludeDirectories(std::list<std::string> dirs);

    std::list<std::string> getIncludeDirectories();

    bool hasIncludes();

                      /*-------------Libraries--------------*/

    void addLibarySearchingPath(std::string dir);

    // Dynamic
    void addDL(std::string name);

    std::list<std::string> getDLs();

    std::list<std::string> getLibarySearchingPaths();

    // Satic
    void addSL(std::string fullname);

    std::string &getSLs();

                      /*--------------Variables-------------*/

    void setVariable(std::string, Value *val);

    Value *getVaribale(std::string name);

    bool contains(std::string name);


    // Name
    std::string getName();

                      /*-----Root, object & ouput paths-----*/
    
    // Main directory of project 
    void setRoot(std::string path);

    std::string getRoot();

    // Path fo .o files
    bool hasObjectsPath();

    void setObjectPath(std::string path);

    std::string getObjectPath();

    void addObjFile(std::string file);

    std::list<std::string> getObjFiles();


    // exe/dll-file path
    bool hasOutputPath();

    void setOutputPath(std::string path);

    std::string getOutputPath();

                      /*--------------Compiler--------------*/

    void setCompiler(std::string name, char standart);

    std::string &getCompiler();

    std::string getStandart();

};

class Projects {
public:
    
    // Table of projects that created in session
    static std::map<std::string, Project*> projects;

    // The project that is being processed
    static Project *target;

    static void init();

    static void finalize();

    //
    static void initProject(std::string name, int version = 0);

};


// system funcions

// Creates new project in heap and returns
// reference to it;
// When program exit deletes all projects
Project &project(std::string name);

// Sets Compiler from current project
void setCompiler(std::string c, char standart = 98);

                    /*-----Root, object & ouput paths-----*/

void setRoot(std::string path);

std::string getRoot();


void setObjectPath(std::string);

std::string getObjectPath();


void setOutputPath(std::string);

std::string getOutputPath();

                    /*---------------Sources--------------*/

void addSourcesPath(std::list< std::string > paths);

void addSourcePath(std::string path);

void addSource(std::list< std::string > files);

void addSource(std::string);

std::list<std::string> getSources();

void addSourceDirectory(std::string dir);

std::list<std::string> getSourceDirectories();

                    /*---------------Include--------------*/

void addInclude(std::string s);

std::list<std::string> getIcludes();

bool hasIncludes();


void setVariable(std::string name, Value *val);

Value* getVariable(std::string name);


void callByName(std::string funcName, std::vector<Value *> arguments);


}