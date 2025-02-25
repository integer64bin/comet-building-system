#pragma once

#include <string>
#include <list>

namespace comet {

struct Configs;

struct CompilerOptions {

    const std::string &flags;

    const std::string &root;

    const std::list<std::string> &includes;

    const std::list<std::string> &dllSearchingPaths;

};

class Compiler {

public:

    /*================================Methods================================*/

    Compiler() = delete;
    Compiler(const Compiler &) = delete;
    Compiler(const Compiler &&) = delete;


    /*============================Static utilities===========================*/

    // Compilation
    // -c -o
    // configs stores information such as headers, sources, 
    // 
    static void compile(CompilerOptions &opts, std::string src, std::string out = "");

    // Linking
    // -o
    static void link(CompilerOptions &opts, std::list<std::string> files);

    static std::string getFlags(std::list<std::string> flags);

    static std::string getFlags(std::initializer_list<std::string> flags);

private:
    

};




}