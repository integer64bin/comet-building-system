#pragma once

#include <string>
#include <list>

namespace comet {

struct Configs;

struct CompilerOptions {

    const std::string &compiler;

    const std::string &flags;

    const std::string &root;

    const std::list<std::string> &includes;

    const std::list<std::string> &dllSearchingPaths;

    const std::list<std::string> &dlls;

};

class Compiler {
public:

    /*================================Methods=================================*/

    Compiler() = delete;
    Compiler(const Compiler &) = delete;
    Compiler(const Compiler &&) = delete;

    /*============================Static variables============================*/

    /**
     * @brief This variable responsible for an output of a debug information 
     * during the building
     */
    static bool debug_info;

    /**
     * @brief This variable responsible for an ignore of errors that occurs 
     * during the building and linking
     */
    static bool ignore_errors;

    /**
     * @brief Stores count of occured errors
     */
    static size_t erros_count;

    /*============================Static utilities============================*/

    /**
     * @brief Calls the compiler for compilation to object file. This method
     * doesn't link target.
     * 
     * @param opts stores information about compiler headers, compilation flags
     * and libaries
     * @param src  the source file that need to compile
     * @param out  the object file for to write to
     */
    static void compile(CompilerOptions &opts, std::string src, std::string out = "");

    /**
     * @brief Calls the compiler linker to link all files that was specified 
     * 
     * @param opts    stores information about compiler headers, compilation flags
     * and libaries
     * @param files   the list of files to link (sources or objects)
     * @param sources if files is a list of source files its need to set true
     *                and to false in another case
     */
    static void link(
        CompilerOptions &opts, 
        std::list<std::string> files, 
        bool sources = false
    );


    // Support
    // Creates string 
    static std::string getFlags(std::list<std::string> flags);

    static std::string getFlags(std::initializer_list<std::string> flags);

private:
    
    // Support methods
    static std::string getIncludeFlags(
        const std::list<std::string> &includes, 
        const std::string root
    );

};




}