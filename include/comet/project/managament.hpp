#pragma once

#include <string>
#include <map>
#include <vector>

#include <ast\value\Value.hpp>
#include <functional>


namespace comet {

class Project;

class Projects {

    /**
     * @brief This variable stores all functions, that can be used by in script
     * 
     */
    static std::map<std::string, std::function<void(Project*, std::vector<Value*>)> > functions;

public:
    
    // Table of projects that created in session
    static std::map<std::string, Project*> projects;

    // The project that is being processed
    static Project *target;

    /**
     * @brief Calls the script function with specified name
     * 
     * @param name name of function
     * @param arguments array of arguments
     * @throw UnknownFunction if function isn't defined 
     */
    static void call(const std::string &name, const std::vector<Value*> &arguments);

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
     * @brief Creates projects with specifies name and version
     * 
     * @param name 
     * @param version 
     */
    static void initProject(std::string name, int version = 0);

    /**
     * @brief 
     * 
     * @return count of projects
     */
    static int count();

    /**
     * @brief Returns 
     * 
     * @param name 
     * @return true  if exists project with specified name
     * @return false 
     */
    static bool contains(const std::string &name);

    /**
     * @brief Returns project by name
     * 
     * @param name 
     * @return Project* 
     */
    static Project *get(const std::string &name);

};

}