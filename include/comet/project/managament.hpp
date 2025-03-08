#pragma once

#include <string>
#include <map>


namespace comet {

class Project;

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

}