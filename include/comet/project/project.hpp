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

    // Allows access to source file by his name
    std::map<std::string, std::string> sourceByName;

    // Contains directories which contains .cpp files
    std::list<std::string> sourceDirectories;

    // List of all objects
    std::list<std::string> objFiles;

    // List object direcotries
    std::list<std::string> objDirectories;

    // Allows access to object files by source file name
    std::map<std::string, std::string> objByName;

    // List of include directories
    std::list<std::string> includeDirectories;

    // Path to object files 
    std::string objectPath = "";

    // Path to executable/library 
    std::string resultPath = "";

    // directories which contains libraries
    std::list<std::string> libFolders;

    // libraries which need to link
    std::list<std::string> libraries;

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
    
    /**
     * @brief Adds source file to list of source files
     * 
     * @param file name of source file 
     */
    void addSource(std::string file);

    /**
     * @brief Get the list of source files
     * 
     * @return std::list<std::string> 
     */
    std::list<std::string> getSources();

    /**
     * @brief Get the full name of source with specified name
     * 
     * @param name name of searched source file
     * @return std::string 
     */
    std::string getSource(const std::string &name);

    /**
     * @brief 
     * 
     * @param name name of source file 
     * @return true  if source file with specified name exists
     * @return false in another case
     */
    bool constainsSource(const std::string &name);
    
    std::map<std::string, std::string> getFilesTable();

    /**
     * @brief Adds direcotory that contains source files
     * 
     * @param dir name of folder
     */
    void addSourceDirectory(std::string dir);
    
    /**
     * @brief Get the list of folders that stores source files
     * 
     * @return std::list<std::string> 
     */
    std::list<std::string> getSourceDirectories();

                      /*--------------Includes--------------*/
    /**
     * @brief Adds one include directory
     * 
     * @param dir name of directory
     */
    void addIncludeDirectory(std::string dir);

    /**
     * @brief Adds the extra includes directories
     * 
     * @param dirs list of directories
     */
    void addIncludeDirectories(std::list<std::string> dirs);

    /**
     * @brief Get the list of directories that contains headers
     * 
     * @return std::list<std::string> 
     */
    std::list<std::string> getIncludeDirectories();

    /**
     * @brief 
     * 
     * @return true  if project has extra includes
     * @return false in another case
     */
    bool hasIncludes();

                      /*-------------Libraries--------------*/

    /**
     * @brief Adds directory that contains libraries
     * 
     * @param dir full name of directory
     */
    void addLibarySearchingPath(std::string dir);

    /**
     * @brief Adds library to link
     * 
     * @param name name of library
     */
    void addLibrary(std::string name);

    /**
     * @brief Get the list of linking libraries
     * 
     * @return std::list<std::string> list of linking libraries
     */
    std::list<std::string> getLibraries();

    /**
     * @brief Get the list of folders that stores libaries
     * 
     * @return std::list<std::string> list of folders that stores libaries 
     */
    std::list<std::string> getLibarySearchingPaths();

                      /*--------------Variables-------------*/

    /**
     * @brief Set the value of a script's varibale with specified name
     * 
     * @param name name of variable
     * @param val new value of variable
     */
    void setVariable(std::string name, Value *val);

    /**
     * @brief Get the value of variable
     * 
     * @param name name of searched variable
     * @return Value* value of variable, but if variable doesn't exist
     * returns nullptr. 
     */
    Value *getVaribale(std::string name);

    /**
     * @brief 
     * 
     * @param name name of searched variable
     * @return true  if variable exists  
     * @return false in another case
     */
    bool contains(std::string name);


    // Name
    std::string getName();

                      /*-----Root, object & ouput paths-----*/
    
    // Main directory of project 
    void setRoot(std::string path);

    /**
     * @brief Get the root folder of project
     * 
     * @return std::string root folder of project
     */
    std::string getRoot();

    // Path fo .o files
    /**
     * @brief 
     * 
     * @return true  if specified folder for object files
     * @return false in another case
     */
    bool hasObjectsPath();

    /**
     * @brief Set the object path of project
     * 
     * @param path the folder where the files are saved
     */
    void setObjectPath(std::string path);

    /**
     * @brief 
     * 
     * @return std::string the folder where the files are saved
     */
    std::string getObjectPath();

    /**
     * @brief Adds object file to list of object files
     * 
     * @param file 
     */
    void addObjFile(std::string file);
    
    /**
     * @brief Get the list of object files
     * This is usful when need compilation with object files
     * 
     * 
     * @return std::list<std::string> 
     */
    std::list<std::string> getObjFiles();

    /**
     * @brief Get full name of object file which corresponds
     * to source file with name.
     * 
     * If name doesn't exist throws comet::CommandError
     * 
     * @param name name of source file
     * @return std::string full name of object file
     * @throws CommandError if name doesn't exist
     */
    std::string getObjFile(const std::string &name);

    /**
     * @brief 
     * 
     * @param name 
     * @return true if name exists 
     * @return false in another case
     */
    bool containsObject(const std::string &name);


    // exe/dll-file path
    /**
     * @brief 
     * 
     * @return true  if specifies output path for executable or library
     * @return false in another case
     */
    bool hasOutputPath();

    /**
     * @brief Set the executable path of project
     * 
     * @param path path to executable's directory
     */
    void setOutputPath(std::string path);

    /**
     * @brief Get the output path
     * 
     * @return std::string 
     */
    std::string getOutputPath();

                      /*--------------Compiler--------------*/

    /**
     * @brief Set the compiler and its standart
     * 
     * @param name      name of compiler
     * @param standart  standart of compiler
     */
    void setCompiler(std::string name, char standart);

    /**
     * @brief Get the name of used compiler
     * 
     * @return std::string& 
     */
    std::string &getCompiler();

    /**
     * @brief Get the used standart
     * 
     * @return std::string 
     */
    std::string getStandart();

};

class Projects {
public:
    
    // Table of projects that created in session
    static std::map<std::string, Project*> projects;

    // The project that is being processed
    static Project *target;

    /**
     * @brief Run a project with specified name and pass him specified
     * arguments
     * 
     * @param name name of project 
     * @param arguments conactenated with arguments with witespace separation
     * @return int
     */
    static int run(const std::string &name, const std::string &arguments);

    /**
     * @brief
     * Initializes projects' manager
     * 
     * This method calls other initialization methods of different 
     * subsystems
     * 
     */
    static void init();

    /**
     * @brief 
     * Deletes all projects
     * 
     * This method calls other finalization methods of different 
     * subsystems
     * 
     */
    static void finalize();

    /**
     * @brief 
     * 
     * @param name 
     * @param version 
     */
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